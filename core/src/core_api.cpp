#include "core_api.h"

CORE_API int CORE_CALL core_abi_version()
{
    return CORE_ABI_VERSION;
}

CORE_API int CORE_CALL core_add(int a, int b)
{
    return a + b;
}