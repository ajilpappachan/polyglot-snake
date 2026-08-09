using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public class Renderer
    {
        private bool _isRunning;
        private float _deltaTime;

        public bool IsRunning => _isRunning;
        public float DeltaTime => _deltaTime;

        public Renderer(int width, int height, string title)
        {
            Raylib.InitWindow(width, height, title);
            _isRunning = true;
            _deltaTime = 0.0f;
        }

        public void Destroy()
        {
            Raylib.CloseWindow();
        }

        public void Update(Grid grid, Snake snake)
        {
            float dt = _deltaTime;

            if(Raylib.IsKeyDown(KeyboardKey.A))
            {
                snake.SetDirection(Direction.Left);
            }
            if(Raylib.IsKeyDown(KeyboardKey.D))
            {
                snake.SetDirection(Direction.Right);
            }
            if(Raylib.IsKeyDown(KeyboardKey.W))
            {
                snake.SetDirection(Direction.Up);
            }
            if(Raylib.IsKeyDown(KeyboardKey.S))
            {
                snake.SetDirection(Direction.Down);
            }

            snake.Update(dt);
        }

        public void Draw(Grid grid, Snake snake)
        {
            _isRunning = !Raylib.WindowShouldClose();

            if (_isRunning)
            {
                Raylib.BeginDrawing();
                Raylib.ClearBackground(Color.Purple);

                foreach(var segment in snake.Segments)
                {
                    (int x, int y) = grid.GridToPixel(segment.GridX, segment.GridY);
                    Raylib.DrawRectangle(x, y, grid.CellSize, grid.CellSize, segment.Color);
                }

                Raylib.EndDrawing();
            }

            _deltaTime = Raylib.GetFrameTime();
        }
    }
}