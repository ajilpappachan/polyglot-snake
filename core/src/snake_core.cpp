#include "snake_core.h"
#include "Game.h"

CORE_API int32_t CORE_CALL snake_core_version(void)
{
    return SNAKE_CORE_VERSION;
}

CORE_API SnakeGame* CORE_CALL snake_create(SnakeConfig config)
{
    if (config.width < 1 || config.height < 1) return nullptr;

    SnakeGame* pGame = (SnakeGame*)(new Game(config.width, config.height));
    return pGame;
}

CORE_API SNAKE_STATUS CORE_CALL snake_destroy(SnakeGame* pGame)
{
    if (pGame == nullptr) return SNAKE_FAILURE;

    delete (Game*)pGame;
    
    return SNAKE_SUCCESS;
}

CORE_API SNAKE_STATUS CORE_CALL snake_grid_dimensions(SnakeGame* pGame, int32_t* out_width, int32_t* out_height)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    if (out_width == nullptr) return SNAKE_FAILURE;
    if (out_height == nullptr) return SNAKE_FAILURE;

    const Grid* grid = ((Game*)pGame)->GetGrid();
    *out_width = grid->GetWidth();
    *out_height = grid->GetHeight();
    
    return SNAKE_SUCCESS;
}

CORE_API SNAKE_STATUS CORE_CALL snake_segment_count(SnakeGame* pGame, int32_t* out_count)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    if (out_count == nullptr) return SNAKE_FAILURE;

    const Snake* pSnake = ((Game*)pGame)->GetSnake();
    *out_count = pSnake->GetSegmentCount();
    
    return SNAKE_SUCCESS;
}

CORE_API SNAKE_STATUS CORE_CALL snake_segment_data_size(SnakeGame* pGame, int32_t* out_size)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    if (out_size == nullptr) return SNAKE_FAILURE;

    const Snake* pSnake = ((Game*)pGame)->GetSnake();
    int segmentCount = pSnake->GetSegmentCount();
    *out_size = segmentCount * 2 * sizeof(int32_t);

    return SNAKE_SUCCESS;
}

CORE_API SNAKE_STATUS CORE_CALL snake_segment_data(SnakeGame* pGame, int32_t bufferSize, int32_t* pBuffer)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    if (pBuffer == nullptr) return SNAKE_FAILURE;

    const Snake* pSnake = ((Game*)pGame)->GetSnake();
    int segmentCount = pSnake->GetSegmentCount();
    int dataSize = segmentCount * 2 * sizeof(int32_t);
    if (bufferSize < dataSize) return SNAKE_FAILURE;

    const std::vector<SnakeSegment>* segments = pSnake->GetSegments();
    for (int i = 0; i < segmentCount; i++)
    {
        int x = 0;
        int y = 0;
        segments->at(i).GetPosition(x, y);
        *(pBuffer + (i * 2)) = x;
        *(pBuffer + (i * 2 + 1)) = y;
    }

    return SNAKE_SUCCESS;
}