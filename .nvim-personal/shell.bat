@echo off

call "c:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
pushd c:\Users\user\dev\home\cpp-playground
nvim .
