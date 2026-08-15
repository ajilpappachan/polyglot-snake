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
    
    CHECK_EQ(gameState.pSegmentData[0].direction, 0);

    int startX = gameState.pSegmentData[0].x;
    int StartY = gameState.pSegmentData[0].y;
    
    status = snake_change_direction(pGame, 2); // Cannot move backwards
    CHECK_EQ(status, SNAKE_SUCCESS);

    status = snake_update(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    CHECK_EQ(gameState.pSegmentData[0].direction, 0);
    CHECK_EQ(gameState.pSegmentData[0].x, startX);
    CHECK_EQ(gameState.pSegmentData[0].y, StartY - 1);

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}