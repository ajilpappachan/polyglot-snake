#ifndef SNAKE_H
#define SNAKE_H

#include "SnakeSegment.h"
#include <vector>

class Snake
{
    public:
    Snake() = delete;
    Snake(int x, int y, Direction direction);
    Snake(const Snake&) = delete;
    Snake& operator= (const Snake&) = delete;
    ~Snake();

    int GetSegmentCount() const;
    const std::vector<SnakeSegment>* GetSegments() const;

    void ChangeDirection(Direction direction);
    void Move();

    private:
    std::vector<SnakeSegment> segments;
    Direction nextDirection;
};

#endif // SNAKE_H