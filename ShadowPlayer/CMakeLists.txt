cmake_minimum_required(VERSION 3.20)

project(shadowplayer-blumia)

option (PREFER_QT_5 "Prefer to use Qt 5" OFF)

if (PREFER_QT_5)
    find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
else()
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
endif()

if (${QT_VERSION_MAJOR} EQUAL "5")
    set(QT_MINIMUM_VERSION "5.15.2")
else()
    set(QT_MINIMUM_VERSION "6.7.3")
endif ()

find_package(Qt${QT_VERSION_MAJOR} ${QT_MINIMUM_VERSION} REQUIRED
    COMPONENTS Core Gui Widgets WinExtras
)

if (${QT_VERSION_MAJOR} EQUAL "6")
    find_package(Qt${QT_DEFAULT_MAJOR_VERSION} ${QT_MINIMUM_VERSION} CONFIG REQUIRED Core5Compat)
endif()

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

if (${QT_VERSION_MAJOR} EQUAL "5")
target_sources(${EXE_NAME}
PRIVATE
    MyGlobalShortCut/MyGlobalShortCut.cpp MyGlobalShortCut/MyGlobalShortCut.h
    MyGlobalShortCut/MyWinEventFilter.cpp MyGlobalShortCut/MyWinEventFilter.h
)
endif()

target_link_libraries(${EXE_NAME}
PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::WinExtras
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

if (${QT_VERSION_MAJOR} EQUAL "6")
    target_link_libraries(${EXE_NAME} PRIVATE Qt6::Core5Compat)
endif()

target_include_directories(${EXE_NAME}
PRIVATE
    3rdparty
)

target_link_directories(${EXE_NAME}
PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdparty/x64
)