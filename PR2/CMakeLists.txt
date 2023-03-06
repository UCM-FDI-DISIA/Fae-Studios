cmake_minimum_required(VERSION 3.23)
project(TPV2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TPV2_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(Practica1
        TPV2/TPV2/src/main.cpp
        TPV2/TPV2/src/json/JSON.cpp
        TPV2/TPV2/src/json/json_demo.cpp
        TPV2/TPV2/src/json/JSONValue.cpp
        TPV2/TPV2/src/sdlutils/SDLUtils.cpp
        TPV2/TPV2/src/sdlutils/sdlutils_demo.cpp
        TPV2/TPV2/src/sdlutils/SoundEffect.cpp
        TPV2/TPV2/src/sdlutils/Texture.cpp
        TPV2/TPV2/src/utils/Collisions.cpp
        TPV2/TPV2/src/utils/Vector2D.cpp
        TPV2/TPV2/src/ecs/Manager.cpp
        TPV2/TPV2/src/game/Game.cpp
        TPV2/TPV2/src/game/AsteroidsManager.cpp
        TPV2/TPV2/src/states/PlayState.cpp
        TPV2/TPV2/src/states/EndState.cpp
        TPV2/TPV2/src/states/EndOfRoundState.cpp
        TPV2/TPV2/src/states/GameStateMachine.cpp
        TPV2/TPV2/src/states/StartState.cpp
        TPV2/TPV2/src/states/PauseState.cpp
        TPV2/TPV2/src/states/WinState.cpp
        TPV2/TPV2/src/components/DeAcceleration.cpp
        TPV2/TPV2/src/components/FighterCtrl.cpp
        TPV2/TPV2/src/components/Gun.cpp
        TPV2/TPV2/src/components/Health.cpp
        TPV2/TPV2/src/components/Image.cpp
        TPV2/TPV2/src/components/ShowAtOpposideSide.cpp
        TPV2/TPV2/src/components/Transform.cpp
        TPV2/TPV2/src/components/FramedImage.cpp
        TPV2/TPV2/src/components/DisableOnExit.cpp
        TPV2/TPV2/src/components/Follow.cpp
        TPV2/TPV2/src/components/Text.cpp
        )
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(Practica1 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})


