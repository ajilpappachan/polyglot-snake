using cs_snake;

Grid grid = new Grid(30, 30, 20);

Snake snake = new Snake(grid.Width / 2, grid.Height / 2);

Renderer renderer = new Renderer(grid.PixelWidth, grid.PixelHeight, "CS_SNAKE");

while (renderer.IsRunning)
{
    renderer.Update(grid, snake);
    renderer.Draw(grid, snake);
}

renderer.Destroy();