#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Snake.h"

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

    private:
    Grid grid;
    Snake snake;
};

#endif // GAME_H