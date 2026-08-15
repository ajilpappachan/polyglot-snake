from ctypes import CDLL, byref, c_int8, c_int32, Structure, POINTER
from pathlib import Path

core_version: int = 4

SNAKE_STATUS = c_int32
SNAKE_SUCCESS = 0
SNAKE_FAILURE = -1

class _Config(Structure):
    _fields_= [
        ("width", c_int32),
        ("height", c_int32)
    ]

class _SnakeGame(Structure):
    pass

class _SnakeSegmentData(Structure):
    _fields_ = [
        ("x", c_int32),
        ("y", c_int32),
        ("direction", c_int32),
        ("color", c_int32),
    ]

class _SnakeGameState(Structure):
    _fields_ = [
        ("isRunning", c_int8),
        ("segmentCount", c_int32),
        ("pSegmentData", POINTER(_SnakeSegmentData)),
    ]

class _Core_ABI:
    def __init__(self, dll_name: str) -> None:
        self.lib = CDLL(Path(__file__).with_name(dll_name))

        self.lib.snake_core_version.restype = c_int32
        self.lib.snake_core_version.argtypes = []

        self.lib.snake_create.restype = POINTER(_SnakeGame)
        self.lib.snake_create.argtypes = [_Config]

        self.lib.snake_destroy.restype = SNAKE_STATUS
        self.lib.snake_destroy.argtypes = [POINTER(_SnakeGame)]

        self.lib.snake_grid_dimensions.restype = SNAKE_STATUS
        self.lib.snake_grid_dimensions.argtypes = [POINTER(_SnakeGame), POINTER(c_int32), POINTER(c_int32)]

        self.lib.snake_game_state.restype = SNAKE_STATUS
        self.lib.snake_game_state.argtypes = [POINTER(_SnakeGame), POINTER(_SnakeGameState)]

        self.lib.snake_change_direction.restype = SNAKE_STATUS
        self.lib.snake_change_direction.argtypes = [POINTER(_SnakeGame), c_int32]

        self.lib.snake_update.restype = SNAKE_STATUS
        self.lib.snake_update.argtypes = [POINTER(_SnakeGame)]

class Core:
    def __init__(self, width: int, height: int) -> None:
        self._ABI = _Core_ABI("snake_core.dll")

        # verify version
        self.version = self._ABI.lib.snake_core_version()
        print(f"Loaded core version {self.version}")
        if self.version != core_version:
            raise RuntimeError("Core version mismatch")

        config = _Config(width, height)
        self._game = self._ABI.lib.snake_create(config)
        if not self._game:
            raise RuntimeError("Failed to create core game")

    def get_grid_dimensions(self)-> tuple[int, int]:
        width = c_int32()
        height = c_int32()
        status = self._ABI.lib.snake_grid_dimensions(self._game, byref(width), byref(height))
        if status != SNAKE_SUCCESS:
            raise RuntimeError("Failed to get grid dimensions")
        return (width.value, height.value)