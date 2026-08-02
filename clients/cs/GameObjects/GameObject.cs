using Raylib_cs;

namespace cs_snake
{
    public class GameObject
    {
        public string name;
        public int x;
        public int y;
        public int width;
        public int height;
        public Color color;

        public GameObject(string _name, int _x, int _y, int _width, int _height, Color _color)
        {
            name = _name;
            x = _x;
            y = _y;
            width = _width;
            height = _height;
            color = _color;
        }

        public virtual void Update(float deltatime)
        {
            // Do nothing
        }

        public virtual void Draw()
        {
            Raylib.DrawRectangle(x, y, width, height, color);
        }
    }
}