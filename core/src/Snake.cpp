#include "Snake.h"
#include "Game.h"

 Snake::Snake(int x, int y, Direction direction, const Game* _pGame)
 :
 segments(),
 nextDirection(direction),
 pGame(_pGame)
 {
    SnakeSegment head(x, y, direction, Color::Green);
    segments.push_back(head);
    segments.push_back(SnakeSegment(x, y + 1, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 2, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 3, direction, Color::White));
    segments.push_back(SnakeSegment(x, y + 4, direction, Color::White));
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
    const Grid* pGrid = this->pGame->GetGrid();
    Direction nextDir = this->nextDirection;
    Direction lastDir;
    for (int i = 0; i < this->segments.size(); i++)
    {
        lastDir = this->segments.at(i).GetDirection();
        this->segments.at(i).SetDirection(nextDir);
        this->segments.at(i).Move();
        int x, y;
        this->segments.at(i).GetPosition(x, y);
        if (x > pGrid->GetWidth() - 1)
        { x = 0; }
        else if (x < 0)
        { x = pGrid->GetWidth() - 1; }
        if (y > pGrid->GetHeight() - 1)
        { y = 0; }
        else if (y < 0)
        { y = pGrid->GetHeight() - 1; }
        this->segments.at(i).SetPosition(x, y);
        nextDir = lastDir;
    }
}

void Snake::Grow()
{
    const Grid* pGrid = this->pGame->GetGrid();
    const SnakeSegment tail = this->segments.back();
    int x, y;
    Direction direction = tail.GetDirection();
    tail.GetPosition(x, y);
    switch(direction)
    {
        case Direction::Up:
            y++;
            break;
        case Direction::Right:
            x--;
            break;
        case Direction::Down:
            y--;
            break;
        case Direction::Left:
            x++;
            break;
        default:
            break;
    }
    if (x > pGrid->GetWidth() - 1)
    { x = 0; }
    else if (x < 0)
    { x = pGrid->GetWidth() - 1; }
    if (y > pGrid->GetHeight() - 1)
    { y = 0; }
    else if (y < 0)
    { y = pGrid->GetHeight() - 1; }
    segments.push_back(SnakeSegment(x, y, direction, Color::White));
}
