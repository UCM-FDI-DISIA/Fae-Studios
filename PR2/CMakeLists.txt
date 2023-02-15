cmake_minimum_required(VERSION 3.24)
project(Ott)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Ott_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


add_executable(Ott
        #MAIN Y SDLAPPLICATION
        "Ott - An Elemental Journey/main.cpp"
        "Ott - An Elemental Journey/SDLApplication.cpp"

        #UI
        "Ott - An Elemental Journey/ui/Button.cpp"
        "Ott - An Elemental Journey/ui/Slider.cpp"
        "Ott - An Elemental Journey/ui/UIText.cpp"
        "Ott - An Elemental Journey/ui/HealthBar.cpp"
        "Ott - An Elemental Journey/ui/ChargedAttackBar.cpp"
        "Ott - An Elemental Journey/ui/ScreenDarkener.cpp"

        #LOADERS
        "Ott - An Elemental Journey/loaders/FontLoader.cpp"
        "Ott - An Elemental Journey/loaders/TextureLoader.cpp"

        #GAMEOBJECTS
        "Ott - An Elemental Journey/gameobjects/GameObject.cpp"
        "Ott - An Elemental Journey/gameobjects/CollisionObject.cpp"
        "Ott - An Elemental Journey/gameobjects/Entity.cpp"
        "Ott - An Elemental Journey/gameobjects/MovingObject.cpp"
        "Ott - An Elemental Journey/gameobjects/Ott/Ott.cpp"
        "Ott - An Elemental Journey/gameobjects/Physics/Ground.cpp"
        "Ott - An Elemental Journey/gameobjects/Mapa.cpp"

        #GAMEFLOW
        "Ott - An Elemental Journey/gameflow/GameState.cpp"
        "Ott - An Elemental Journey/gameflow/GameStateMachine.cpp"
        "Ott - An Elemental Journey/gameflow/menus/MainMenuState.cpp"
        "Ott - An Elemental Journey/gameflow/menus/PauseMenuState.cpp"
        "Ott - An Elemental Journey/gameflow/menus/MenuState.cpp"
        "Ott - An Elemental Journey/gameflow/menus/options/MusicOptionsMenuState.cpp"
        "Ott - An Elemental Journey/gameflow/menus/options/OptionsMenuState.cpp"
        "Ott - An Elemental Journey/gameflow/menus/options/ControlMenuState.cpp"
        "Ott - An Elemental Journey/gameflow/play/PlayState.cpp"

        #DEPENDENCIES
        "Ott - An Elemental Journey/dependencies/Font.cpp"
        "Ott - An Elemental Journey/dependencies/Parser.cpp"
        "Ott - An Elemental Journey/dependencies/Texture.cpp"
        "Ott - An Elemental Journey/dependencies/Vector2D.cpp"
        "Ott - An Elemental Journey/framework.h"
        "Ott - An Elemental Journey/Resource.h"
        "Ott - An Elemental Journey/targetver.h")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} "/usr/local/include")
target_link_libraries(Ott ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} "/usr/local/lib/libtmxlite.dylib")