@echo off
if not exist build ( mkdir build )
pushd build

echo Compiling...
REM zig c++ -g ..\sources\main.cpp -I "..\libs\CppBenchmark-d3d78dd\include" -fno-lto -O0 -o main.exe

REM zig c++ ^
REM     -I "..\libs\CppBenchmark-d3d78dd\include" ^
REM     -L "..\libs\CppBenchmark-d3d78dd\bin" ^
REM     -l cppbenchmark ^
REM     -g ..\sources\main_test_bench.cpp ^
REM     -O0 -o main.exe

cl /EHsc ^
    /MD ^
    /std:c++20 ^
    /O2 ^
    -I..\libs\CppBenchmark-d3d78dd\include ^
    ..\sources\main_test_bench.cpp ^
    ..\libs\CppBenchmark-d3d78dd\bin\cppbenchmark.lib ^
    ..\libs\CppBenchmark-d3d78dd\temp\modules\Release\HdrHistogram.lib user32.lib advapi32.lib ^
    /Femain.exe

if %errorlevel% neq 0 (
    echo.
    echo Compilation [31mFailed[0m

    popd
    exit %errorlevel%
)

echo.
echo Compilation [32mSucceeded[0m

popd

