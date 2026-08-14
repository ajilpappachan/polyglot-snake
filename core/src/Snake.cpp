#include "Snake.h"

 Snake::Snake(int x, int y, Direction direction)
 :
 segments()
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