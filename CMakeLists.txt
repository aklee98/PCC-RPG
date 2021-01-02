cmake_minimum_required(VERSION 3.13)
project(SFMLApp)
//This file needs to be changed based on the directory of a user's installed SFML.
set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "/home/user/Development/sfmlbuild/include")
set(SFML_LIBRARY_DIR "/home/user/Development/sfmlbuild/lib")
set(SFML_DIR "/home/user/Development/sfmlbuild/lib/cmake/SFML")
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
    
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(SFMLApp main.cpp GameFiles/Game.cpp GameFiles/Game.h
        GameFiles/Game_Interface.cpp GameFiles/Game_Interface.h GameFiles/GameText.cpp GameFiles/GameText.h
        GameFiles/Thumbnail.cpp GameFiles/Thumbnail.h)
target_link_libraries (SFMLApp sfml-graphics sfml-window sfml-system)
