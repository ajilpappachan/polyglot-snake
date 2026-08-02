from enum import Enum, auto

from pygame import Color, Rect, Surface
import pygame

from gameobject import GameObject

class Direction(Enum):
    INVALID = auto()
    UP      = auto()
    DOWN    = auto()
    LEFT    = auto()
    RIGHT   = auto()

class Snake(GameObject):
    def __init__(self, x: int, y: int, size: int) -> None:
        super().__init__(x, y, size, size, Color(255, 255, 255))
        self.size = size

    def draw(self, screen: Surface) -> None:
        pygame.draw.rect(screen, self.color, Rect(self.x, self.y, self.width, self.height))
