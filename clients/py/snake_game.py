from ctypes import CDLL, c_float, c_int
from pathlib import Path

core_version: int = 1

# CORE HEADER SHAPE

# int snake_core_version();

# int snake_game_width();
# int snake_game_height();

# void snake_init();
# void snake_update(float deltatime);
# void snake_destroy();

# int snake_snake_segments();
# int snake_segment_position_x(int segment);
# int snake_segment_position_y(int segment);

class SnakeGame:
    def __init__(self, dll_name) -> None:
        self.lib = CDLL(Path(__file__).with_name(dll_name))

        # verify version
        self.lib.snake_core_version.restype = c_int
        self.lib.snake_core_version.argtypes = []
        lib_version = self.lib.snake_core_version()
        print(f"Loaded core version {lib_version}")
        assert(lib_version == core_version)

        self.lib.snake_game_width.restype =  c_int
        self.lib.snake_game_width.argtypes = []
        self.lib.snake_game_height.restype =  c_int
        self.lib.snake_game_height.argtypes = []
        self.lib.snake_init.restype =  None
        self.lib.snake_init.argtypes = []
        self.lib.snake_update.restype =  None
        self.lib.snake_update.argtypes = [c_float]
        self.lib.snake_destroy.restype =  None
        self.lib.snake_destroy.argtypes = []
        self.lib.snake_snake_segments.restype =  c_int
        self.lib.snake_snake_segments.argtypes = []
        self.lib.snake_segment_position_x.restype =  c_int
        self.lib.snake_segment_position_x.argtypes = [c_int]
        self.lib.snake_segment_position_y.restype =  c_int
        self.lib.snake_segment_position_y.argtypes = [c_int]

    def core_version(self) -> int:
        return self.lib.snake_core_version()

    def game_width(self) -> int:
        return self.lib.snake_game_width()

    def game_height(self) -> int:
        return self.lib.snake_game_height()

    def init(self) -> None:
        self.lib.snake_init()

    def update(self, deltatime: float) -> None:
        self.lib.snake_update(deltatime)

    def destroy(self) -> None:
        self.lib.snake_destroy()

    def snake_segments(self) -> int:
        return self.lib.snake_snake_segments()

    def segment_position(self, segment: int) -> tuple[int, int]:
        return (self.lib.snake_segment_position_x(segment),
                self.lib.snake_segment_position_y(segment)) 