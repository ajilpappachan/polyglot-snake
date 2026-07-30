REM This will build core and copy the dll/wasm files to relavant clients

cmake -S core -B core/build
cmake --build core/build

ctest --test-dir core/build -C Debug smoke

emcc core/src/core_api.cpp ^
    -I core/include/ ^
    -o core/build/Debug/core_lib.mjs ^
    --emit-tsd core_lib.d.mts ^
    "-sEXPORTED_FUNCTIONS=_core_abi_version,_core_add" ^
    "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap" ^
    "-sENVIRONMENT=web" ^
    "-sSINGLE_FILE=1"


copy /Y "core\build\Debug\core.dll" "clients\py\"

copy /Y "core\build\Debug\core.dll" "clients\cs\"

if not exist "clients\ts\libs\" mkdir "clients\ts\libs"
copy /Y "core\build\Debug\core_lib.mjs" "clients\ts\libs\"
copy /Y "core\build\Debug\core_lib.d.mts" "clients\ts\libs\"
