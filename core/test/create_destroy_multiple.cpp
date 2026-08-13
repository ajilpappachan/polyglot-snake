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

    status = snake_destroy(pGameA);
    CHECK_EQ(status, SNAKE_SUCCESS);
    status = snake_destroy(pGameB);
    CHECK_EQ(status, SNAKE_SUCCESS);

    return 0;
}