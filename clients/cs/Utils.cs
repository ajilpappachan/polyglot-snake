using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public enum Direction : Int32
    {
        Up,
        Right,
        Down,
        Left
    }

    public enum Color : Int32
    {
        Green,
        White,
        Blue
    }

    public static class Utils
    {
        public static Raylib_cs.Color GetRenderColor(Color color)
        {
            Raylib_cs.Color renderColor = Raylib_cs.Color.Pink;

            switch (color)
            {
                case Color.Green:
                    renderColor = Raylib_cs.Color.Green;
                    break;
                case Color.White:
                    renderColor = Raylib_cs.Color.White;
                    break;
                case Color.Blue:
                    renderColor = Raylib_cs.Color.Blue;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            return renderColor;
        }
    }
}