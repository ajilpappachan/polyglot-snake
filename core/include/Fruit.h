#ifndef FRUIT_H
#define FRUIT_H

#include "Utils.h"

class Game;

class Fruit
{
    public:
    Fruit() = delete;
    Fruit(int x, int y, Color color, const Game* pGame);
    Fruit(const Fruit&) = delete;
    Fruit& operator= (const Fruit&) = delete;
    ~Fruit();

    void Respawn();
    void GetPosition(int& x, int& y) const;
    Color GetColor() const;

    private:
    int x;
    int y;
    Color color;
    const Game* pGame;
};

#endif // FRUIT_H