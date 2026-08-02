#include "snake_core.h"

#define CORE_VERSION 1

#define GAME_WIDTH 30
#define GAME_HEIGHT 30

CORE_API int CORE_CALL snake_core_version()
{
    return CORE_VERSION;
}

CORE_API int CORE_CALL snake_game_width()
{
    return GAME_WIDTH;
}
CORE_API int CORE_CALL snake_game_height()
{
    return GAME_HEIGHT;
}

CORE_API void CORE_CALL snake_init()
{
    // TODO
}
CORE_API void CORE_CALL snake_update(float deltatime)
{
    // TODO
}
CORE_API void CORE_CALL snake_destroy()
{
    // TODO
}

CORE_API int CORE_CALL snake_snake_segments()
{
    return 1;
}
CORE_API int CORE_CALL snake_segment_position_x(int segment)
{
    return 14;
}
CORE_API int CORE_CALL snake_segment_position_y(int segment)
{
    return 14;
}