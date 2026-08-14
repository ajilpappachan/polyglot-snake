#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int _x, int _y, Direction _direction, Color _color)
:
x(_x),
y(_y),
direction(_direction),
color(_color)
{
}

SnakeSegment::SnakeSegment(const SnakeSegment& segment)
:
x(segment.x),
y(segment.y),
direction(segment.direction)
{
}

SnakeSegment& SnakeSegment::operator= (const SnakeSegment& segment)
{
    this->x = segment.x;
    this->y = segment.y;
    this->direction = segment.direction;
    return *this;
}

SnakeSegment::~SnakeSegment()
{
}

void SnakeSegment::SetPosition(const int _x, const int _y)
{
    this->x = _x;
    this->y = _y;
}
void SnakeSegment::GetPosition(int& _x, int& _y) const
{
    _x = this->x;
    _y = this->y;
}

void SnakeSegment::SetDirection(const Direction _direction)
{
    this->direction = _direction;
}
Direction SnakeSegment::GetDirection() const
{
    return this->direction;
}

void SnakeSegment::SetColor(const Color _color)
{
    this->color = _color;
}

Color SnakeSegment::GetColor() const
{
    return this->color;
}