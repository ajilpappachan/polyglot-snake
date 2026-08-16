from enum import IntEnum

class Direction(IntEnum):
    Up = 0
    Right = 1
    Down = 2
    Left = 3

class Color(IntEnum):
    Green = 0
    White = 1
    Blue = 2

class Utils:
    @classmethod
    def get_render_color(cls, color: Color) -> str:
        out = str()
        match color:
            case Color.Green:
                out = "green"
            case Color.White:
                out = "white"
            case Color.Blue:
                out = "blue"
            case _:
                assert False, "unknown color"
        return out
