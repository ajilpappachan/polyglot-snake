#include "test_shared.h"

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    const int GridWidth = 30;
    const int GridHeight = 30;

    SNAKE_STATUS status;
    SnakeGame* pGame;
    
    pGame = snake_create(SnakeConfig({GridWidth, GridHeight}));
    CHECK(pGame != nullptr);

    SnakeGameState gameState;
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    CHECK_EQ(gameState.pSegmentData[0].direction, 0);

    int headStartX = gameState.pSegmentData[0].x;
    int segStartX = gameState.pSegmentData[1].x;

    // Move till overlap
    for (int i = 0; i < GridWidth / 2 + 1; i++)
    {
        status = snake_update(pGame);
        CHECK_EQ(status, SNAKE_SUCCESS);
    }
    
    status = snake_game_state(pGame, &gameState);
    CHECK_EQ(status, SNAKE_SUCCESS);
    
    CHECK_EQ(gameState.pSegmentData[0].direction, 0);
    CHECK_EQ(gameState.pSegmentData[0].x, headStartX);
    CHECK_EQ(gameState.pSegmentData[0].y, GridHeight - 1);
    CHECK_EQ(gameState.pSegmentData[1].direction, 0);
    CHECK_EQ(gameState.pSegmentData[1].x, segStartX);
    CHECK_EQ(gameState.pSegmentData[1].y, 0);

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}