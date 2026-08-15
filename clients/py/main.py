from core import Core
from renderer import Renderer

if __name__ == "__main__":
    core = Core(30, 30)
    renderer = Renderer(core, 20)

    while renderer.running:
        renderer.update()
        renderer.draw()

    renderer.destroy()