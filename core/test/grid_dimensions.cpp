#include "test_shared.h"

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    int32_t status;
    SnakeGame* pGameA;
    SnakeGame* pGameB;
    
    pGameA = snake_create(SnakeConfig({30, 30}));
    CHECK(pGameA != nullptr);
    pGameB = snake_create(SnakeConfig({20, 10}));
    CHECK(pGameB != nullptr);

    int32_t width, height;
    width = snake_grid_width(pGameA);
    CHECK_EQ(width, 30);
    height = snake_grid_height(pGameA);
    CHECK_EQ(height, 30);
    width = snake_grid_width(pGameB);
    CHECK_EQ(width, 20);
    height = snake_grid_height(pGameB);
    CHECK_EQ(height, 10);

    status = snake_destroy(pGameA);
    CHECK_EQ(status, SNAKE_SUCCESS);
    status = snake_destroy(pGameB);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}