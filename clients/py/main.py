from gameobject import GameObjectMan
from renderer import Renderer
from snake import Snake

render = Renderer(600, 600)
snake = Snake(600//2 - 20, 600//2 - 20, 20)
GameObjectMan.add("snake", snake)

while render.running:
    print(f"FPS: {render.deltatime_s()}")
    render.poll_events()

    GameObjectMan.update(render.deltatime_s())

    render.draw()

render.destroy()