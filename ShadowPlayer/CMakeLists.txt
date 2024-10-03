cmake_minimum_required(VERSION 3.12)

project(shadowplayer-blumia)

find_package(Qt5 5.15.2 REQUIRED
    COMPONENTS Core Gui Widgets WinExtras
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXE_NAME "ShadowPlayer")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${EXE_NAME} WIN32)

target_compile_definitions(${EXE_NAME}
PRIVATE
    UNICODE
    _UNICODE
)

target_sources(${EXE_NAME}
PRIVATE
    main.cpp
    shadowplayer.cpp shadowplayer.h
    player.cpp player.h
    lyricsmanager.cpp lyricsmanager.h
    lrcbar.cpp lrcbar.h
    spslider.cpp spslider.h
    playlist.cpp playlist.h
    MyGlobalShortCut/MyGlobalShortCut.cpp MyGlobalShortCut/MyGlobalShortCut.h
    MyGlobalShortCut/MyWinEventFilter.cpp MyGlobalShortCut/MyWinEventFilter.h
    osd.cpp osd.h
    fftdisplay.cpp fftdisplay.h
    shadowlabel.cpp shadowlabel.h
    mini.cpp mini.h
    thread.cpp thread.h

    shadowplayer.ui
    lrcbar.ui
    playlist.ui
    osd.ui
    mini.ui

    res.qrc
    ShadowPlayer.rc
)

target_link_libraries(${EXE_NAME}
PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::WinExtras
    bass.lib
    tags.lib
    bassape.lib
    bass_aac.lib
    bassalac.lib
    bass_tta.lib
    bassflac.lib
    basswma.lib
    basswv.lib
    bass_fx.lib
)

target_include_directories(${EXE_NAME}
PRIVATE
    3rdparty
)

target_link_directories(${EXE_NAME}
PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdparty/x64
)