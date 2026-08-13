#include "Game.h"

Game::Game(int width, int height)
:
grid(width, height)
{
}

Game::~Game()
{
}

const Grid* Game::GetGrid() const
{
    return &this->grid;
}