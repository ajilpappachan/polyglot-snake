using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public enum Direction
    {
        Invalid,
        Up,
        Down,
        Left,
        Right
    }

    public class SnakeSegment : GameObject
    {
        public Direction direction;

        private float realX;
        private float realY;
        private float speed;

        public SnakeSegment(string _name, float _x, float _y, int _size, Color _color, float _speed, Direction _direction)
            :
            base(_name, (int)_x, (int)_y, _size, _size, _color)
        {
            Debug.Assert(_speed > 0);
            Debug.Assert(_direction != Direction.Invalid);
            
            realX = _x;
            realY = _y;
            speed = _speed;
            direction = _direction;
        }

        public override void Update(float deltatime)
        {
            switch(direction)
            {
                case Direction.Up:
                    realY += speed * deltatime;
                    break;
                case Direction.Down:
                    realY -= speed * deltatime;
                    break;
                case Direction.Right:
                    realX += speed * deltatime;
                    break;
                case Direction.Left:
                    realX -= speed * deltatime;
                    break;
                case Direction.Invalid:
                default:
                    Debug.Assert(false);
                    break;
            }
        }

        public override void Draw()
        {
            x = (int)MathF.Floor(realX);
            y = (int)MathF.Floor(realY);
            base.Draw();
        }
    }
}