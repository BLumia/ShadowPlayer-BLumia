set QTDIR=C:/Users/Gary/aqt/5.15.2/msvc2019_64

set VSLANG=1033
set PATH=%PATH%;%QTDIR%/bin
set QT_PLUGIN_PATH=%QTDIR%/plugins

if "%1"=="help" goto :help

if "%1"=="debug" (
    set M_BUILD_TYPE=Debug
) else (
    set M_BUILD_TYPE=Release
)

if "%1"=="fresh" (
    set M_CMAKE_CFG_ARGS=--fresh
) else (
    set M_CMAKE_CFG_ARGS=
)

if "%1"=="vs2022" (
    goto :vs2022
)

:build
cmake . -Bbuild %M_CMAKE_CFG_ARGS% || goto :error
cmake --build build --config %M_BUILD_TYPE% || goto :error

:deploy
windeployqt --no-translations --no-opengl-sw --no-system-d3d-compiler build/%M_BUILD_TYPE%/ShadowPlayer.exe
robocopy ../bass-bin/x64 build/%M_BUILD_TYPE% *.dll
echo Successfully built and deployed in %M_BUILD_TYPE% mode.
goto :eof

:: -------------------------------------------------
:vs2022
cmake . -Bbuild -G "Visual Studio 17 2022" || goto :error
goto :eof

:: -------------------------------------------------
:help
echo off
echo %~nx0			: default Release build
echo %~nx0 fresh		: fresh build, CMake will reconfig, require CMake 3.24
echo %~nx0 debug		: debug build
echo %~nx0 vs2022		: generate vs 2022 solution
echo %~nx0 help		: see this help
exit /b

:: -------------------------------------------------
:error
echo Failed with error
exit /b