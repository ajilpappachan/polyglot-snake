#include "core_api.h"
#include <cstdio>

int main()
{
    int fails = 0;
    int status = 0;

    if (core_abi_version() != 1)
    {
        fails++;
        std::printf("Core: Incorrect ABI Version\n");
    }

    if (core_add(2, 4) != 6)
    {
        fails++;
        std::printf("Core: Incorrect add() return\n");
    }

    if (fails > 0)
    {
        std::printf("Core: %d tests failed.\n", fails);
        status = -1;
    }
    else
    {
        std::printf("Core: all tests passed.\n");
        status = 0;
    }

    return status;
}