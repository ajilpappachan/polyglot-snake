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

    int headStartX = gameState.pSegmentData[0].x;
    int headStartY = gameState.pSegmentData[0].y;
    int segStartX = gameState.pSegmentData[1].x;
    int segStartY = gameState.pSegmentData[1].y;
    
    status = snake_change_direction(pGame, 1); // Turn Right
    CHECK_EQ(status, SNAKE_SUCCESS);

    status = snake_update(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    CHECK_EQ(gameState.pSegmentData[0].direction, 1);
    CHECK_EQ(gameState.pSegmentData[0].x, headStartX + 1);
    CHECK_EQ(gameState.pSegmentData[0].y, headStartY);
    CHECK_EQ(gameState.pSegmentData[1].x, segStartX);
    CHECK_EQ(gameState.pSegmentData[1].y, segStartY - 1);

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}