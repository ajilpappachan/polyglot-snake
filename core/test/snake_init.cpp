#include "test_shared.h"

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    SNAKE_STATUS status;
    SnakeGame* pGame;
    
    pGame = snake_create(SnakeConfig({30, 30}));
    CHECK(pGame != nullptr);

    int segmentsCount;
    status = snake_segment_count(pGame, &segmentsCount);
    CHECK_EQ(status, SNAKE_SUCCESS);
    CHECK_EQ(segmentsCount, 7); // TEMPORARY!!

    int startPositions[] = {
        30/2, 30/2,
        30/2, 30/2 + 1,
        30/2, 30/2 + 2,
        30/2, 30/2 + 3,
        30/2, 30/2 + 4,
        30/2, 30/2 + 5,
        30/2, 30/2 + 6,
    };

    int bufferSize = 0;
    status = snake_segment_data_size(pGame, &bufferSize);
    CHECK_EQ(bufferSize, segmentsCount * 2 * (int)sizeof(int));
    char* pBuffer = new char[bufferSize];
    status = snake_segment_data(pGame, bufferSize, (int32_t*)pBuffer);
    CHECK_EQ(status, SNAKE_SUCCESS);

    for (int i = 0; i < segmentsCount; i++)
    {
        int* pSegmentsData = (int*)pBuffer;
        int x = pSegmentsData[i * 2];
        int y = pSegmentsData[i * 2 + 1];
        CHECK_EQ(x, startPositions[i * 2]);
        CHECK_EQ(y, startPositions[i * 2 + 1]);
    }

    delete[] pBuffer;

    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}