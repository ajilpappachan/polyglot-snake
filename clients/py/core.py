from ctypes import CDLL, byref, c_int8, c_int32, Structure, POINTER
from pathlib import Path
from typing import NamedTuple

from utils import Color, Direction

core_version: int = 4

SNAKE_STATUS = c_int32
SNAKE_SUCCESS = 0
SNAKE_FAILURE = -1

class _C_Config(Structure):
    _fields_= [
        ("width", c_int32),
        ("height", c_int32)
    ]

class _Config(NamedTuple):
    width: int
    height: int

class _C_SnakeGame(Structure):
    pass

class _C_SegmentData(Structure):
    _fields_ = [
        ("x", c_int32),
        ("y", c_int32),
        ("direction", c_int32),
        ("color", c_int32),
    ]

class SegmentData(NamedTuple):
    x: int
    y: int
    direction: Direction
    color: Color

class _C_GameState(Structure):
    _fields_ = [
        ("isRunning", c_int8),
        ("segmentCount", c_int32),
        ("pSegmentData", POINTER(_C_SegmentData)),
    ]

class GameState(NamedTuple):
    isRunning: bool
    segmentData: list[SegmentData]

class _Core_ABI:
    _lib = CDLL(Path(__file__).with_name("snake_core.dll"))
    _lib.snake_core_version.restype = c_int32
    _lib.snake_core_version.argtypes = []
    _lib.snake_create.restype = POINTER(_C_SnakeGame)
    _lib.snake_create.argtypes = [_C_Config]
    _lib.snake_destroy.restype = SNAKE_STATUS
    _lib.snake_destroy.argtypes = [POINTER(_C_SnakeGame)]
    _lib.snake_grid_dimensions.restype = SNAKE_STATUS
    _lib.snake_grid_dimensions.argtypes = [POINTER(_C_SnakeGame), POINTER(c_int32), POINTER(c_int32)]
    _lib.snake_game_state.restype = SNAKE_STATUS
    _lib.snake_game_state.argtypes = [POINTER(_C_SnakeGame), POINTER(_C_GameState)]
    _lib.snake_change_direction.restype = SNAKE_STATUS
    _lib.snake_change_direction.argtypes = [POINTER(_C_SnakeGame), c_int32]
    _lib.snake_update.restype = SNAKE_STATUS
    _lib.snake_update.argtypes = [POINTER(_C_SnakeGame)]

    @classmethod
    def snake_core_version(cls) -> int:
        return cls._lib.snake_core_version()

    @classmethod
    def snake_create(cls, config: _Config) -> int:
        c_config = _C_Config(config.width, config.height)
        return cls._lib.snake_create(c_config)

    @classmethod
    def snake_destroy(cls, game_ptr: int) -> int:
        return cls._lib.snake_destroy(game_ptr)

    @classmethod
    def snake_grid_dimensions(cls, game_ptr: int) -> tuple[int, int, int]:
        width = c_int32()
        height = c_int32()
        status = cls._lib.snake_grid_dimensions(game_ptr, byref(width), byref(height))
        return (status, width.value, height.value)

    @classmethod
    def snake_game_state(cls, game_ptr: int) -> tuple[int, GameState]:
        c_state = _C_GameState()
        status = cls._lib.snake_game_state(game_ptr, byref(c_state))
        isRunning = bool(c_state.isRunning)
        segments = [
            SegmentData(s.x, s.y, Direction(s.direction), Color(s.color))
            for s in c_state.pSegmentData[:c_state.segmentCount]
        ]
        state = GameState(isRunning, segments)
        return (status, state)

    @classmethod
    def snake_change_direction(cls, game_ptr: int, direction: Direction) -> int:
        status = cls._lib.snake_change_direction(game_ptr, direction)
        return status

    @classmethod
    def snake_update(cls, game_ptr: int) -> int:
        status = cls._lib.snake_update(game_ptr)
        return status
    

class Core:
    def __init__(self, width: int, height: int) -> None:
        # verify version
        self.version = _Core_ABI.snake_core_version()
        print(f"Loaded core version {self.version}")
        if self.version != core_version:
            raise RuntimeError("Core version mismatch")
        config = _Config(width, height)
        self._game = _Core_ABI.snake_create(config)
        if not self._game:
            raise RuntimeError("Failed to create core game")
        self.current_state = GameState(True, [])

    def destroy(self) -> None:
        status = _Core_ABI.snake_destroy(self._game)
        if status != SNAKE_SUCCESS:
            raise RuntimeError("Failed to destroy core game")

    def get_grid_dimensions(self) -> tuple[int, int]:
        (status, width, height) = _Core_ABI.snake_grid_dimensions(self._game)
        if status != SNAKE_SUCCESS:
            raise RuntimeError("Failed to get grid dimensions")
        return (width, height)

    def change_direction(self, direction: Direction) -> None:
        status = _Core_ABI.snake_change_direction(self._game, direction)
        if status != SNAKE_SUCCESS:
            raise RuntimeError("Failed to change direction")

    def update(self) -> None:
        status = _Core_ABI.snake_update(self._game)
        if status != SNAKE_SUCCESS:
            raise RuntimeError("Failed to update core game")
        (status, state) = _Core_ABI.snake_game_state(self._game)
        if status != SNAKE_SUCCESS:
            raise RuntimeError("Failed to get game state")
        self.current_state = state