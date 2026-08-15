import pygame

from core import Core

class Renderer:
    def __init__(self, core: Core, cellSize: int) -> None:
        pygame.init()
        (width, height) = core.get_grid_dimensions()
        self.screen = pygame.display.set_mode((width * cellSize, height * cellSize))
        self.clock = pygame.Clock()
        self.running = True

    def destroy(self) -> None:
        pygame.quit()

    def update(self) -> None:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False

    def draw(self) -> None:
        self.screen.fill("purple")

        pygame.display.flip()
        self.clock.tick(60)

    def deltatime(self) -> float:
        return self.clock.get_time() / 1000
