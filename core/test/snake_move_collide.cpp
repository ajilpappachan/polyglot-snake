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
    
    CHECK_EQ(gameState.pSegmentData[0].direction, 0);

    // This test is probably going to lock me into a starting state of 4 segments 
    // unless i come up with a better system.
    
    status = snake_change_direction(pGame, 1); // Turn Right
    CHECK_EQ(status, SNAKE_SUCCESS);

    status = snake_update(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    status = snake_change_direction(pGame, 2); // Turn Down
    CHECK_EQ(status, SNAKE_SUCCESS);

    status = snake_update(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    status = snake_change_direction(pGame, 3); // Turn Left, collide
    CHECK_EQ(status, SNAKE_SUCCESS);

    status = snake_update(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);

    CHECK_EQ((bool)gameState.isRunning, false);

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}