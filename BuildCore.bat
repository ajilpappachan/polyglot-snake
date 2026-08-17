REM This will build core and copy the dll/wasm files to relavant clients

cmake -S core -B core/build
if errorlevel 1 exit /b 1
cmake --build core/build
if errorlevel 1 exit /b 1

ctest --test-dir core/build -C Debug --no-tests=error --output-on-failure
if errorlevel 1 exit /b 1

em++ ^
    core/src/snake_core.cpp ^
    core/src/Game.cpp ^
    core/src/Grid.cpp ^
    core/src/SnakeSegment.cpp ^
    core/src/Snake.cpp ^
    -I core/include/ ^
    -o core/build/Debug/snake_core.mjs ^
    --emit-tsd snake_core.d.mts ^
    "-sEXPORTED_FUNCTIONS=_malloc,_free" ^
    "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap,getValue,setValue,stackSave,stackAlloc,stackRestore" ^
    "-sENVIRONMENT=web,node" ^
    "-sASSERTIONS=1" ^
    "-sSINGLE_FILE=1"
if errorlevel 1 exit /b 1


copy /Y "core\build\Debug\snake_core.dll" "clients\py\"
if errorlevel 1 exit /b 1

copy /Y "core\build\Debug\snake_core.dll" "clients\cs\"
if errorlevel 1 exit /b 1

if not exist "clients\ts\libs\" mkdir "clients\ts\libs"
if errorlevel 1 exit /b 1
copy /Y "core\build\Debug\snake_core.mjs" "clients\ts\libs\"
if errorlevel 1 exit /b 1
copy /Y "core\build\Debug\snake_core.d.mts" "clients\ts\libs\"
if errorlevel 1 exit /b 1