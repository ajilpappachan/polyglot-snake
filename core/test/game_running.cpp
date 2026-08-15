#include "test_shared.h"

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    SNAKE_STATUS status;
    SnakeGame* pGame;
    
    pGame = snake_create(SnakeConfig({30, 30}));
    CHECK(pGame != nullptr);

    SnakeGameState gameState;
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    CHECK_EQ((bool)gameState.isRunning, true);

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}