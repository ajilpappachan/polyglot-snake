#include "test_shared.h"

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    int32_t status;
    SnakeGame* pGame;

    pGame = snake_create(SnakeConfig({-1, 0}));
    CHECK(pGame == nullptr);
    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_FAILURE);
    
    pGame = snake_create(SnakeConfig({30, 30}));
    CHECK(pGame != nullptr);
    status = snake_destroy(pGame);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}