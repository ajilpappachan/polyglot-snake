#include "Game.h"

Game::Game(int width, int height)
:
grid(width, height),
snake(width / 2, height / 2, Direction::Up),
isRunning(true)
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

bool Game::IsGameRunning() const
{
    return this->isRunning;
}

void Game::ChangeDirection(Direction direction)
{
    this->snake.ChangeDirection(direction);
}

void Game::Update()
{
    if (!this->isRunning) return;

    this->snake.Move();

    SnakeSegment head = this->snake.GetSegments()->at(0);
    int headX, headY, segX, segY;
    head.GetPosition(headX, headY);

    for (int i = 1; i < this->snake.GetSegmentCount(); i++)
    {
        SnakeSegment segment = this->snake.GetSegments()->at(i);
        segment.GetPosition(segX, segY);
        if (headX == segX && headY == segY)
        {
            this->isRunning = false; // Snake Collided
        }
    }
}