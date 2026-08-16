import pygame

from core import Core
from utils import Color, Direction, Utils

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
        self._core_update_frequency = 1.0
        self._time_since_core_update = 0.0

    def destroy(self) -> None:
        pygame.quit()

    def update(self) -> None:
        change_direction = False
        new_direction = Direction.Up
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.is_running = False
            if event.type == pygame.KEYDOWN:
                match event.key:
                    case pygame.K_w | pygame.K_UP:
                        change_direction = True
                        new_direction = Direction.Up
                    case pygame.K_d | pygame.K_RIGHT:
                        change_direction = True
                        new_direction = Direction.Right
                    case pygame.K_s | pygame.K_DOWN:
                        change_direction = True
                        new_direction = Direction.Down
                    case pygame.K_a | pygame.K_LEFT:
                        change_direction = True
                        new_direction = Direction.Left
                    case _:
                        pass
        if not self._core.current_state.isRunning:
            return
        if change_direction:
            self._core.change_direction(new_direction)
        if self._time_since_core_update > self._core_update_frequency:
            self._core.update()
            self._time_since_core_update = 0.0
            print("update core")
        self._time_since_core_update += self.deltatime()

    def draw(self) -> None:
        self._screen.fill("purple")
        game_state = self._core.current_state
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
            font = pygame.font.SysFont("consolas", 32)
            text_surface = font.render("Game Over!", False, Utils.get_render_color(Color.White))
            self._screen.blit(text_surface, (self._width / 2 - text_surface.width / 2, 0))
        pygame.display.flip()
        self._clock.tick(60)

    def deltatime(self) -> float:
        return self._clock.get_time() / 1000
