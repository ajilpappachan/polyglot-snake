#include "Snake.h"

 Snake::Snake(int x, int y, Direction direction)
 :
 segments(),
 nextDirection(direction)
 {
    SnakeSegment head(x, y, direction, Color::Green);
    segments.push_back(head);

    // TEMPORARY
    segments.push_back(SnakeSegment(x, y + 1, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 2, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 3, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 4, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 5, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 6, direction, Color::White));
 }

Snake::~Snake()
{
    this->segments.clear();
}

 int Snake::GetSegmentCount() const
 {
    return (int)this->segments.size();
 }

const std::vector<SnakeSegment>* Snake::GetSegments() const
{
    return &this->segments;
}

void Snake::ChangeDirection(Direction direction)
{
    Direction currDirection = this->segments[0].GetDirection();
    Direction revDirection = (Direction)(((int)currDirection + 2) % 4); // Clockwise order direction, wrap around after 3
    if (direction != revDirection)
    {
        this->nextDirection = direction;
    }
}

void Snake::Move()
{
    Direction nextDir = this->nextDirection;
    Direction lastDir;
    for (int i = 0; i < this->segments.size(); i++)
    {
        lastDir = this->segments.at(i).GetDirection();
        this->segments.at(i).SetDirection(nextDir);
        this->segments.at(i).Move();
        nextDir = lastDir;
    }
}
