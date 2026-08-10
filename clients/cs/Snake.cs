using Raylib_cs;

namespace cs_snake
{
    public class Snake
    {
        private List<SnakeSegment> _segments;
        
        private float _speed;
        private float _lastMove;

        public List<SnakeSegment> Segments => _segments;

        public Snake(int gridX, int gridY)
        {
            _segments = new List<SnakeSegment>();
            _segments.Add(new SnakeSegment(gridX, gridY    , Color.Green, Direction.Up));
            _segments.Add(new SnakeSegment(gridX, gridY + 1, Color.White, Direction.Up));
            _segments.Add(new SnakeSegment(gridX, gridY + 2, Color.White, Direction.Up));
            _segments.Add(new SnakeSegment(gridX, gridY + 3, Color.White, Direction.Up));
            _segments.Add(new SnakeSegment(gridX, gridY + 4, Color.White, Direction.Up));
            _segments.Add(new SnakeSegment(gridX, gridY + 5, Color.White, Direction.Up));
            _segments.Add(new SnakeSegment(gridX, gridY + 6, Color.White, Direction.Up));
            _speed = 1.0f;
            _lastMove = 0.0f;
        }

        public void Update(float deltaTime)
        {
            _lastMove += deltaTime;
            if (_lastMove > _speed)
            {
                SnakeSegment head = _segments[0];

                Direction nextDirection = head.Direction;
                foreach (var segment in _segments)
                {
                    Direction currDirection = segment.Direction;
                    segment.Move();
                    segment.SetDirection(nextDirection);
                    nextDirection = currDirection;
                }
                _lastMove = 0.0f;

                // Check collision
                foreach (var segment in _segments)
                {
                    if (segment != head
                        && segment.GridX == head.GridX
                        && segment.GridY == head.GridY)
                    {
                        Game.GetInstance().IsRunning = false;
                    }
                }
            }
        }

        public void SetDirection(Direction direction)
        {
            if (_segments.Count == 1 
                || DirectionUtils.Reverse(_segments[1].Direction) != direction)
            {
                _segments[0].SetDirection(direction);
            }
        }
    }
}