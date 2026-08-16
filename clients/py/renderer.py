import pygame

from core import Core
from utils import Color, Utils

class Renderer:
    def __init__(self, title: str, core: Core, cellSize: int) -> None:
        pygame.init()
        (width, height) = core.get_grid_dimensions()
        self._core = core
        self._cellSize = cellSize
        self._width = width * cellSize
        self._height = height * cellSize
        self._screen = pygame.display.set_mode((self._width, self._height))
        pygame.display.set_caption(title)
        self._clock = pygame.Clock()
        self.is_running = True

    def destroy(self) -> None:
        pygame.quit()

    def update(self) -> None:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.is_running = False

    def draw(self) -> None:
        self._screen.fill("purple")

        game_state = self._core.get_game_state()

        for segment in game_state.segmentData:
            pygame.draw.rect(
                self._screen, 
                Utils.get_render_color(segment.color), 
                pygame.Rect(
                    segment.x * self._cellSize, 
                    segment.y * self._cellSize, 
                    self._cellSize, 
                    self._cellSize))

        if not game_state.isRunning:
            font = pygame.font.SysFont(pygame.font.get_default_font(), self._cellSize)
            text_surface = font.render("Game Over!", True, Utils.get_render_color(Color.White))
            self._screen.blit(text_surface, (0, 0))

        pygame.display.flip()
        self._clock.tick(60)

    def deltatime(self) -> float:
        return self._clock.get_time() / 1000
