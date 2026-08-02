import pygame

from snake_game import SnakeGame

game = SnakeGame("core.dll")
width = game.game_width()
height = game.game_height()
grid_size = 20

pygame.init()
screen = pygame.display.set_mode((width * 20, height * 20))
clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill("purple")

    position = game.segment_position(0)
    pygame.draw.rect(screen, "white", (position[0] * grid_size, position[1] * grid_size, grid_size, grid_size))

    pygame.display.flip()

    clock.tick(60)

pygame.quit()