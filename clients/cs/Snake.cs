using Raylib_cs;

namespace cs_snake
{
    public class Snake
    {
        private Queue<SnakeSegment> _segments;

        public Queue<SnakeSegment> Segments => _segments;

        public Snake(int gridX, int gridY)
        {
            _segments = new Queue<SnakeSegment>();
            _segments.Enqueue(new SnakeSegment(gridX, gridY    , Color.Green, Direction.Up));
            _segments.Enqueue(new SnakeSegment(gridX, gridY + 1, Color.White, Direction.Up));
            _segments.Enqueue(new SnakeSegment(gridX, gridY + 2, Color.White, Direction.Up));
            _segments.Enqueue(new SnakeSegment(gridX, gridY + 3, Color.White, Direction.Up));
            _segments.Enqueue(new SnakeSegment(gridX, gridY + 4, Color.White, Direction.Up));
            _segments.Enqueue(new SnakeSegment(gridX, gridY + 5, Color.White, Direction.Up));
            _segments.Enqueue(new SnakeSegment(gridX, gridY + 6, Color.White, Direction.Up));
        }

        public void Update(float deltaTime)
        {
            Direction prevDirection = _segments.Peek().Direction;
            foreach (var segment in _segments)
            {
                Direction direction = prevDirection;
                prevDirection = segment.Direction;
                segment.Update(deltaTime, direction);
            }
        }

        public void SetDirection(Direction direction)
        {
            _segments.Peek().SetDirection(direction);
        }
    }
}