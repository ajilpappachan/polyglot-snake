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

    private:
    std::vector<SnakeSegment> segments;
};

#endif // SNAKE_H