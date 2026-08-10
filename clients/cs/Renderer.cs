using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public class Renderer
    {
        private bool _shouldClose;
        private float _deltaTime;

        public float DeltaTime => _deltaTime;
        public bool ShouldClose => _shouldClose;

        public Renderer(int width, int height, string title)
        {
            Raylib.InitWindow(width, height, title);
            _deltaTime = 0.0f;
        }

        public void Destroy()
        {
            Raylib.CloseWindow();
        }

        public void Update()
        {
            Game game = Game.GetInstance();
            if (!game.IsRunning)
            {
                return;
            }

            float dt = _deltaTime;

            Snake snake = game.Snake;

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

        public void Draw()
        {
            _shouldClose = Raylib.WindowShouldClose();

            Game game = Game.GetInstance();

            if (!_shouldClose)
            {
                Raylib.BeginDrawing();
                Raylib.ClearBackground(Color.Purple);

                Grid grid = game.Grid;
                Snake snake = game.Snake;

                foreach(var segment in snake.Segments)
                {
                    (int x, int y) = grid.GridToPixel(segment.GridX, segment.GridY);
                    Raylib.DrawRectangle(x, y, grid.CellSize, grid.CellSize, segment.Color);
                }

                if (!game.IsRunning)
                {
                    Raylib.DrawText("Game Over!", 0, 0, 18, Color.White);
                }

                Raylib.EndDrawing();
            }

            _deltaTime = Raylib.GetFrameTime();
        }
    }
}