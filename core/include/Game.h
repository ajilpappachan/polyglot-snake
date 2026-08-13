#ifndef GAME_H
#define GAME_H

#include "Grid.h"

class Game
{    
    public:
    Game() = delete;
    Game(int width, int height);
    Game(const Game&) = delete;
    Game& operator= (const Game&) = delete;
    ~Game();

    const Grid* GetGrid() const;

    private:
    Grid grid;
};

#endif // GAME_H