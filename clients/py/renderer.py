import pygame

from gameobject import GameObjectMan

class Renderer:
    def __init__(self, width: int, height: int) -> None:
        pygame.init()
        self.screen = pygame.display.set_mode((width, height))
        self.clock = pygame.Clock()
        self.running = True

    def destroy(self) -> None:
        pygame.quit()

    def poll_events(self) -> None:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False

    def draw(self) -> None:
        self.screen.fill("purple")
        GameObjectMan.draw(self.screen)

        pygame.display.flip()
        self.clock.tick(60)

    def deltatime_ms(self) -> int:
        return self.clock.get_time()

    def deltatime_s(self) -> float:
        return self.clock.get_time() / 1000
