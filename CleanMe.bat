@echo off
setlocal enabledelayedexpansion

set "root=%~dp0"
echo Cleaning %root%

REM Clean Files
set "targets=tmp dll"

for %%e in (%targets%) do (
    for /R "%root%" %%f in (*.%%e) do (
        echo deleting file "%%f"
        del /q "%%f"
    )
)

REM Clean Directories
set "targets=build __pycache__ .vs bin obj node_modules dist libs"

for %%d in (%targets%) do (
    for /D /R "%root%" %%D in (%%d) do (
        if exist "%%D" (
            echo deleting directory "%%D"
            rmdir /s /q "%%D"
        )
    )
)

endlocal