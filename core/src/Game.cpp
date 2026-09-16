#include "Game.h"

Game::Game(int width, int height)
:
grid(width, height),
snake(width / 2, height / 2, Direction::Up, this),
fruit(0, 0, Color::Red, this),
isRunning(true)
{
    this->privRespawnFruit();
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

const Fruit* Game::GetFruit() const
{
    return &this->fruit;
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
    this->privCheckSnakeSelfCollision();
    if (!this->isRunning) return;

    this->privCheckFruitCollision();
}

void Game::privCheckSnakeSelfCollision()
{
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

void Game::privCheckFruitCollision()
{
    SnakeSegment head = this->snake.GetSegments()->at(0);
    int headX, headY;
    head.GetPosition(headX, headY);
    int fruitX, fruitY;
    this->fruit.GetPosition(fruitX, fruitY);
    if (headX == fruitX && headY == fruitY) // Collision with Fruit
    {
        this->privRespawnFruit();
    } 
}

void Game::privRespawnFruit()
{
    bool isValidPosition = true;
    do
    {
        int fruitX, fruitY, segX, segY;    
        this->fruit.Respawn();
        this->fruit.GetPosition(fruitX, fruitY);
        for (int i = 0; i < this->snake.GetSegmentCount(); i++)
        {
            SnakeSegment segment = this->snake.GetSegments()->at(i);
            segment.GetPosition(segX, segY);
            if (fruitX == segX && fruitY == segY)
            {
                isValidPosition = false; // Fruit overlap with snake
            }
        }
    } while (isValidPosition == false);
}