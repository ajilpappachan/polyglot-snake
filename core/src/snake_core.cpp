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

CORE_API SNAKE_STATUS CORE_CALL snake_game_state(SnakeGame* pGame, SnakeGameState* pState)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    if (pState == nullptr) return SNAKE_FAILURE;

    const Snake* pSnake = ((Game*)pGame)->GetSnake();
    const SnakeSegment* pSegments = pSnake->GetSegments()->data();

    pState->segmentCount = pSnake->GetSegmentCount();
    pState->pSegmentData = (const SnakeSegmentData*)pSegments;

    return SNAKE_SUCCESS;
}