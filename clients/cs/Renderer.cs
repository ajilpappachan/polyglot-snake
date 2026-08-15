using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public class Renderer
    {
        private bool _shouldClose;
        private float _deltaTime;
        private int _cellSize;
        private Core _core;

        private float _timeSinceCoreUpdate;
        private float _coreUpdateFrequency;

        public float DeltaTime => _deltaTime;
        public bool ShouldClose => _shouldClose;
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
            Raylib.InitWindow(width * cellSize, height * cellSize, title);

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

            if(Raylib.IsKeyDown(KeyboardKey.A))
            {
                _core.ChangeDirection(Direction.Left);
            }
            if(Raylib.IsKeyDown(KeyboardKey.D))
            {
                _core.ChangeDirection(Direction.Right);
            }
            if(Raylib.IsKeyDown(KeyboardKey.W))
            {
                _core.ChangeDirection(Direction.Up);
            }
            if(Raylib.IsKeyDown(KeyboardKey.S))
            {
                _core.ChangeDirection(Direction.Down);
            }

            _timeSinceCoreUpdate += Raylib.GetFrameTime();
            if (_timeSinceCoreUpdate > _coreUpdateFrequency)
            {
                _core.Update();
                _timeSinceCoreUpdate = 0;
            }
        }

        public void Draw()
        {
            _shouldClose = Raylib.WindowShouldClose();

            Game game = Game.GetInstance();

            if (!_shouldClose)
            {
                Raylib.BeginDrawing();
                Raylib.ClearBackground(Raylib_cs.Color.Purple);

                Core.GameState gameState = _core.CurrentState;

                foreach (var segment in gameState.segmentData)
                {
                    int x = segment.x * _cellSize;
                    int y = segment.y * _cellSize;
                    Raylib.DrawRectangle(x, y, _cellSize, _cellSize, Utils.GetRenderColor(segment.color));
                }

                if (!_core.CurrentState.isRunning)
                {
                    Raylib.DrawText("Game Over!", 0, 0, 18, Raylib_cs.Color.White);
                }

                Raylib.EndDrawing();
            }

            _deltaTime = Raylib.GetFrameTime();
        }
    }
}