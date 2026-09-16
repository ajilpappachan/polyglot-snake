#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Snake.h"
#include "Fruit.h"

class Game
{    
    public:
    Game() = delete;
    Game(int width, int height);
    Game(const Game&) = delete;
    Game& operator= (const Game&) = delete;
    ~Game();

    const Grid* GetGrid() const;
    const Snake* GetSnake() const;
    const Fruit* GetFruit() const;

    bool IsGameRunning() const;

    void ChangeDirection(Direction direction);
    void Update();

    private:
    void privCheckSnakeSelfCollision();
    void privCheckFruitCollision();
    void privRespawnFruit();

    private:
    Grid grid;
    Snake snake;
    Fruit fruit;
    bool isRunning;
};

#endif // GAME_H