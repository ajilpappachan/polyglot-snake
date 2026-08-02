using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public class Window
    {
        private static Window? sInstance;

        public static void Init(int width, int height, string title)
        {
            Debug.Assert(sInstance == null);
            sInstance = new Window(width, height, title);
        }

        public static void Destroy()
        {
            Debug.Assert(sInstance != null);
            sInstance.privDestroy();
            sInstance = null;
        }

        public static bool IsRunning()
        {
            Debug.Assert(sInstance != null);
            return sInstance.isRunning;
        }

        public static float GetDeltatime()
        {
            Debug.Assert(sInstance != null);
            return Raylib.GetFrameTime();
        }

        public static void Draw()
        {
            Debug.Assert(sInstance != null);
            sInstance.privDraw();
        }

        private bool isRunning;

        private Window(int width, int height, string title)
        {
            Raylib.InitWindow(width, height, title);
            isRunning = true;
        }

        private void privDestroy()
        {
            Raylib.CloseWindow();
        }

        private void privDraw()
        {
            isRunning = !Raylib.WindowShouldClose();

            if (isRunning)
            {
                Raylib.BeginDrawing();
                Raylib.ClearBackground(Color.Purple);

                GameObjectMan.Draw();

                Raylib.EndDrawing();
            }
        }
    }
}