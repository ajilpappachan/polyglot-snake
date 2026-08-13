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
CORE_API int32_t CORE_CALL snake_destroy(SnakeGame* pGame)
{
    if (pGame == nullptr) return SNAKE_FAILURE;

    delete (Game*)pGame;
    return SNAKE_SUCCESS;
}

CORE_API int32_t CORE_CALL snake_grid_width(SnakeGame* pGame)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    
    return ((Game*)pGame)->GetGrid()->GetWidth();
}
CORE_API int32_t CORE_CALL snake_grid_height(SnakeGame* pGame)
{
    if (pGame == nullptr) return SNAKE_FAILURE;
    
    return ((Game*)pGame)->GetGrid()->GetHeight();
}