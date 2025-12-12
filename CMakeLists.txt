cmake_minimum_required(VERSION 3.16)

project(VoicemeeterTrayControl LANGUAGES CXX)

enable_language(RC) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(voicemeeter_tray_control WIN32 
    src/main.cpp

    src/VoicemeeterApi.cpp
    src/VolumeListener.cpp
    src/Tray.cpp
    src/WinAudio.cpp
)

target_sources(voicemeeter_tray_control PRIVATE
    ${CMAKE_SOURCE_DIR}/appicon.rc 
)

target_include_directories(voicemeeter_tray_control PRIVATE inc)

if (WIN32)
    target_link_libraries(voicemeeter_tray_control PRIVATE
        user32
        kernel32
    )
endif()
