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
    
    CHECK_EQ(gameState.segmentCount, 7); // TEMPORARY!!

    int32_t startData[] = { // x, y, direction, color
        30/2, 30/2,     0, 0,
        30/2, 30/2 + 1, 0, 1,
        30/2, 30/2 + 2, 0, 1,
        30/2, 30/2 + 3, 0, 1,
        30/2, 30/2 + 4, 0, 1,
        30/2, 30/2 + 5, 0, 1,
        30/2, 30/2 + 6, 0, 1,
    };

    for (int i = 0; i < gameState.segmentCount; i++)
    {
        const SnakeSegmentData segmentData = gameState.pSegmentData[i];
        CHECK_EQ(segmentData.x,         startData[i * 4 + 0]);
        CHECK_EQ(segmentData.y,         startData[i * 4 + 1]);
        CHECK_EQ(segmentData.direction, startData[i * 4 + 2]);
        CHECK_EQ(segmentData.color,     startData[i * 4 + 3]);
    }

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}