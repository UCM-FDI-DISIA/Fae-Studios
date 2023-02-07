cmake_minimum_required(VERSION 3.24)
project(Ott)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Ott_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


add_executable(Ott
        "Ott - An Elemental Journey/framework.h"
        "Ott - An Elemental Journey/Ott - An Elemental Journey.cpp"
        "Ott - An Elemental Journey/Ott - An Elemental Journey.h"
        "Ott - An Elemental Journey/Resource.h"
        "Ott - An Elemental Journey/targetver.h")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(Ott ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})