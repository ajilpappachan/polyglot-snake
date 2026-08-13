#include "snake_core.h"
#include "stdio.h"

#define CHECK(cond) do { \
    if (!(cond)) \
    { \
        printf("FAIL: %s. %s:%d\n", #cond, __FILE__, __LINE__); \
        return -1; \
    } \
} while (0)

#define CHECK_EQ(actual, expected) do { \
    if ((actual) != (expected)) \
    { \
        printf("FAIL: %s Expected %d, Actual: %d. %s:%d\n", #actual, expected, actual, __FILE__, __LINE__); \
        return -1; \
    } \
} while (0)
