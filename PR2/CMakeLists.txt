cmake_minimum_required(VERSION 3.24)
project(Ott)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Ott_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


add_executable(Ott
        #MAIN
        "Ott - An Elemental Journey/src/main.cpp"

        #COMPONENTES
        "Ott - An Elemental Journey/src/components/Button.cpp"
        "Ott - An Elemental Journey/src/components/FramedImage.cpp"
        "Ott - An Elemental Journey/src/components/Image.cpp"
        "Ott - An Elemental Journey/src/components/Slider.cpp"
        "Ott - An Elemental Journey/src/components/Text.cpp"
        "Ott - An Elemental Journey/src/components/Transform.cpp"

        #ECS
        "Ott - An Elemental Journey/src/ecs/Manager.cpp"

        #GAME
        "Ott - An Elemental Journey/src/game/Game.cpp"

        #JSON
        "Ott - An Elemental Journey/src/json/JSON.cpp"
        "Ott - An Elemental Journey/src/json/json_demo.cpp"
        "Ott - An Elemental Journey/src/json/JSONValue.cpp"

        #SDLUTILS
        "Ott - An Elemental Journey/src/sdlutils/SDLUtils.cpp"
        "Ott - An Elemental Journey/src/sdlutils/Texture.cpp"
        "Ott - An Elemental Journey/src/sdlutils/SoundEffect.cpp"

        #STATES
        "Ott - An Elemental Journey/src/states/GameStateMachine.cpp"
        "Ott - An Elemental Journey/src/states/PlayState.cpp"
        "Ott - An Elemental Journey/src/states/menus/MenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/MainMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/PauseMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/OptionsMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/MusicOptionsMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/ControlMenuState.cpp"

        #UTILS
        "Ott - An Elemental Journey/src/utils/Collisions.cpp"
        "Ott - An Elemental Journey/src/utils/Vector2D.cpp"
        )

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} "/usr/local/include")
target_link_libraries(Ott ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} "/usr/local/lib/libtmxlite.dylib")