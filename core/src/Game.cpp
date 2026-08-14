#include "Game.h"

Game::Game(int width, int height)
:
grid(width, height),
snake(width / 2, height / 2, Direction::Up)
{
}

Game::~Game()
{
}

const Grid* Game::GetGrid() const
{
    return &this->grid;
}

const Snake* Game::GetSnake() const
{
    return &this->snake;
}