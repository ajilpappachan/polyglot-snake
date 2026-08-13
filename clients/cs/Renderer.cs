using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public class Renderer
    {
        private bool _shouldClose;
        private float _deltaTime;
        private int _cellSize;

        public float DeltaTime => _deltaTime;
        public bool ShouldClose => _shouldClose;
        public int CellSize => _cellSize;

        public Renderer(string title, int gridWidth, int gridHeight, int cellSize)
        {
            Debug.Assert(gridWidth > 0);
            Debug.Assert(gridHeight > 0);
            Debug.Assert(cellSize > 0);
            _deltaTime = 0.0f;
            _cellSize = cellSize;
            Raylib.InitWindow(gridWidth * cellSize, gridHeight * cellSize, title);
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

                Snake snake = game.Snake;

                foreach(var segment in snake.Segments)
                {
                    int x = segment.GridX * _cellSize;
                    int y = segment.GridY * _cellSize;
                    Raylib.DrawRectangle(x, y, _cellSize, _cellSize, segment.Color);
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