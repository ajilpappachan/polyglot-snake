#ifndef SNAKE_H
#define SNAKE_H

#include "SnakeSegment.h"
#include <vector>

class Game;

class Snake
{
    public:
    Snake() = delete;
    Snake(int x, int y, Direction direction, const Game* pGame);
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
    const Game* pGame;
};

#endif // SNAKE_H