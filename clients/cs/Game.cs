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
        public Core Core;
        public Renderer Renderer;

        private Game()
        {
            IsRunning = true;
            Core = new Core(30, 30);
            Renderer = new Renderer("CS_SNAKE", Core, 20);
        }

        public void Run()
        {
            while (!Renderer.ShouldClose)
            {
                Renderer.Update();
                Core.Update();
                Renderer.Draw();
            }

            Renderer.Destroy();
            Core.Destroy();
        }


    }
}