#include "test_shared.h"

int main()
{
    CHECK_EQ(snake_core_version(), SNAKE_CORE_VERSION);

    SNAKE_STATUS status;
    SnakeGame* pGameA;
    SnakeGame* pGameB;
    
    pGameA = snake_create(SnakeConfig({30, 30}));
    CHECK(pGameA != nullptr);
    pGameB = snake_create(SnakeConfig({20, 10}));
    CHECK(pGameB != nullptr);

    int32_t width, height;
    status = snake_grid_dimensions(pGameA, &width, &height);
    CHECK_EQ(status, SNAKE_SUCCESS);
    CHECK_EQ(width, 30);
    CHECK_EQ(height, 30);
    status = snake_grid_dimensions(pGameB, &width, &height);
    CHECK_EQ(status, SNAKE_SUCCESS);
    CHECK_EQ(width, 20);
    CHECK_EQ(height, 10);

    status = snake_destroy(pGameA);
    CHECK_EQ(status, SNAKE_SUCCESS);
    status = snake_destroy(pGameB);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}