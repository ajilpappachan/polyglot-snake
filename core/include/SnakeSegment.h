#ifndef SNAKESEGMENT_H
#define SNAKESEGMENT_H

#include "Utils.h"

class SnakeSegment
{
    public:
    SnakeSegment() = delete;
    SnakeSegment(int x, int y, Direction direction, Color color);
    SnakeSegment(const SnakeSegment& segment);
    SnakeSegment& operator= (const SnakeSegment& segment);
    ~SnakeSegment();

    void SetPosition(const int x, const int y);
    void GetPosition(int& x, int& y) const;

    void SetDirection(const Direction direction);
    Direction GetDirection() const;

    void SetColor(const Color color);
    Color GetColor() const;

    private:
    int x;
    int y;
    Direction direction;
    Color color;
};

#endif // SNAKESEGMENT_H