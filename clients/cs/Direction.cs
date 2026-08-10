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

    public static class DirectionUtils
    {
        public static Direction Reverse(Direction direction)
        {
            Direction reverse = direction;

            switch(direction)
            {
                case Direction.Up:
                    reverse = Direction.Down;
                    break;
                case Direction.Down:
                    reverse = Direction.Up;
                    break;
                case Direction.Left:
                    reverse = Direction.Right;
                    break;
                case Direction.Right:
                    reverse = Direction.Left;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            Debug.Assert(reverse != direction);

            return reverse;
        }
    }
}