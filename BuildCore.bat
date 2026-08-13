REM This will build core and copy the dll/wasm files to relavant clients

cmake -S core -B core/build
if errorlevel 1 exit /b 1
cmake --build core/build
if errorlevel 1 exit /b 1

ctest --test-dir core/build -C Debug --no-tests=error --output-on-failure
if errorlevel 1 exit /b 1

@REM emcc core/src/core_api.cpp ^
@REM     -I core/include/ ^
@REM     -o core/build/Debug/core_lib.mjs ^
@REM     --emit-tsd core_lib.d.mts ^
@REM     "-sEXPORTED_FUNCTIONS=_core_abi_version,_core_add" ^
@REM     "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap" ^
@REM     "-sENVIRONMENT=web" ^
@REM     "-sSINGLE_FILE=1"


@REM copy /Y "core\build\Debug\snake_core.dll" "clients\py\"

copy /Y "core\build\Debug\snake_core.dll" "clients\cs\"
if errorlevel 1 exit /b 1

@REM if not exist "clients\ts\libs\" mkdir "clients\ts\libs"
@REM copy /Y "core\build\Debug\core_lib.mjs" "clients\ts\libs\"
@REM copy /Y "core\build\Debug\core_lib.d.mts" "clients\ts\libs\"
