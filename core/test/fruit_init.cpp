#include "test_shared.h"
#include <cstdlib>

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    SNAKE_STATUS status;
    SnakeGame* pGame;

    const int GRID_WIDTH = 30;
    const int GRID_HEIGHT = 30;
    
    pGame = snake_create(SnakeConfig({GRID_WIDTH, GRID_HEIGHT, 0}));
    CHECK(pGame != nullptr);

    SnakeGameState gameState;
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    CHECK(gameState.fruitData.x > -1);
    CHECK(gameState.fruitData.y < GRID_WIDTH);
    CHECK(gameState.fruitData.y > 0);
    CHECK(gameState.fruitData.y < GRID_HEIGHT);
    CHECK_EQ(gameState.fruitData.color, 2);

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}