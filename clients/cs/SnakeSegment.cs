using Raylib_cs;
using System.Diagnostics;

namespace cs_snake
{
    public enum Direction
    {
        Up,
        Down,
        Left,
        Right
    }

    public class SnakeSegment
    {
        private int _gridX;
        private int _gridY;
        private Color _color;
        private Direction _direction;

        private float _speed;
        private float _lastMove;

        public int GridX => _gridX;
        public int GridY => _gridY;
        public Color Color => _color;
        public Direction Direction => _direction;

        public SnakeSegment(int gridX, int gridY, Color color, Direction direction)
        {
            _gridX = gridX;
            _gridY = gridY;
            _color = color;
            _direction = direction;
            _speed = 1.0f;
            _lastMove = 0.0f;
        }

        public void Update(float deltaTime, Direction direction)
        {
            _lastMove += deltaTime;
            if (_lastMove > _speed)
            {
                switch(_direction)
                {
                    case Direction.Up:
                        _gridY--;
                        break;
                    case Direction.Down:
                        _gridY++;
                        break;
                    case Direction.Left:
                        _gridX--;
                        break;
                    case Direction.Right:
                        _gridX++;
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }

                _lastMove = 0.0f;
                _direction = direction;
            }
        }

        public void SetDirection(Direction direction)
        {
            _direction = direction;
        }
    }
}