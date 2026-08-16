from core import Core
from renderer import Renderer

if __name__ == "__main__":
    core = Core(30, 30)
    renderer = Renderer("py_snake", core, 20)

    while renderer.is_running:
        renderer.update()
        renderer.draw()

    renderer.destroy()
    core.destroy()