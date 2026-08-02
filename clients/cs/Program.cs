using cs_snake;
using Raylib_cs;

Window.Init(600, 600, "CS_SNAKE");
GameObjectMan.Init();

GameObject snake = new SnakeSegment("segment_0", 600 / 2 - 20, 600 / 2 - 20, 20, Color.White, 2, Direction.Up);
GameObjectMan.Add(snake);

while (Window.IsRunning())
{
    GameObjectMan.Update(Window.GetDeltatime());
    Window.Draw();
}

GameObjectMan.Destroy();
Window.Destroy();

