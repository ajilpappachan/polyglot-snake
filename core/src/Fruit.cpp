#include "Fruit.h"
#include "Game.h"

Fruit::Fruit(int _x, int _y, Color _color, const Game* _pGame)
:
x(_x),
y(_y),
color(_color),
pGame(_pGame)
{
}

Fruit::~Fruit()
{
}

void Fruit::Respawn()
{
    const Grid* pGrid = this->pGame->GetGrid();
    int width = pGrid->GetWidth();
    int height = pGrid->GetHeight();
    this->x = std::rand() % width;
    this->y = std::rand() % height;
}

void Fruit::GetPosition(int& _x, int& _y) const
{
    _x = this->x;
    _y = this->y;
}

Color Fruit::GetColor() const
{
    return this->color;
}