using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public class Renderer
    {
        private bool _shouldClose;
        private float _deltaTime;
        private int _cellSize;
        private int _width;
        private int _height;
        private Core _core;

        private float _timeSinceCoreUpdate;
        private float _coreUpdateFrequency;

        public float DeltaTime => _deltaTime;
        public bool ShouldClose => _shouldClose;
        public int Width => _width;
        public int Height => _height;
        public int CellSize => _cellSize;

        public Renderer(string title, Core core, int cellSize)
        {
            _core = core;
            (int width, int height) = core.GetGridDimensions();
            Debug.Assert(width > 0);
            Debug.Assert(height > 0);
            Debug.Assert(cellSize > 0);
            _deltaTime = 0.0f;
            _cellSize = cellSize;
            _width = width * cellSize;
            _height = height * cellSize;
            Raylib.InitWindow(_width, _height, title);
            _timeSinceCoreUpdate = 0;
            _coreUpdateFrequency = 1;
        }

        public void Destroy()
        {
            Raylib.CloseWindow();
        }

        public void Update()
        {
            if (!_core.CurrentState.isRunning)
            {
                return;
            }

            if(Raylib.IsKeyDown(KeyboardKey.W) || Raylib.IsKeyDown(KeyboardKey.Up))
            {
                _core.ChangeDirection(Direction.Up);
            }
            if(Raylib.IsKeyDown(KeyboardKey.D) || Raylib.IsKeyDown(KeyboardKey.Right))
            {
                _core.ChangeDirection(Direction.Right);
            }
            if(Raylib.IsKeyDown(KeyboardKey.S) || Raylib.IsKeyDown(KeyboardKey.Down))
            {
                _core.ChangeDirection(Direction.Down);
            }
            if(Raylib.IsKeyDown(KeyboardKey.A) || Raylib.IsKeyDown(KeyboardKey.Left))
            {
                _core.ChangeDirection(Direction.Left);
            }

            if (_timeSinceCoreUpdate > _coreUpdateFrequency)
            {
                _core.Update();
                _timeSinceCoreUpdate = 0;
            }
            _timeSinceCoreUpdate += Raylib.GetFrameTime();
        }

        public void Draw()
        {
            _shouldClose = Raylib.WindowShouldClose();

            Game game = Game.GetInstance();

            if (!_shouldClose)
            {
                Raylib.BeginDrawing();
                Raylib.ClearBackground(Raylib_cs.Color.Purple);

                GameState gameState = _core.CurrentState;

                foreach (var segment in gameState.segmentData)
                {
                    int x = segment.x * _cellSize;
                    int y = segment.y * _cellSize;
                    Raylib.DrawRectangle(x, y, _cellSize, _cellSize, Utils.GetRenderColor(segment.color));
                }

                if (!_core.CurrentState.isRunning)
                {
                    string text = "Game Over!";
                    int fontSize = 32;
                    int textWidth = Raylib.MeasureText(text, fontSize);
                    Raylib.DrawText(
                        text, 
                        _width / 2 - textWidth / 2, 0, 
                        fontSize,
                        Raylib_cs.Color.White);
                }

                Raylib.EndDrawing();
            }

            _deltaTime = Raylib.GetFrameTime();
        }
    }
}