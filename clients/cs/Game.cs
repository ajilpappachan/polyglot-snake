using System.Diagnostics;

namespace cs_snake
{
    public class Game
    {
        private static Game? sInstance;

        public static void Init()
        {
            Debug.Assert(sInstance == null);
            sInstance = new Game();
        }

        public static Game GetInstance()
        {
            Debug.Assert(sInstance != null);
            return sInstance;
        }

        public bool IsRunning;
        public Renderer Renderer;
        public Grid Grid;
        public Snake Snake;

        private Game()
        {
            IsRunning = true;
            Grid = new Grid(30, 30, 20);
            Snake = new Snake(Grid.Width / 2, Grid.Height / 2);
            Renderer = new Renderer(Grid.PixelWidth, Grid.PixelHeight, "CS_SNAKE");
        }

        public void Run()
        {
            while (!Renderer.ShouldClose)
            {
                Renderer.Update();
                Renderer.Draw();
            }

            Renderer.Destroy();
        }


    }
}