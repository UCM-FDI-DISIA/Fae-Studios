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
        "Ott - An Elemental Journey/src/components/TextComponent.cpp"
        "Ott - An Elemental Journey/src/components/Bullet.cpp"
        "Ott - An Elemental Journey/src/components/CameraComponent.cpp"
        "Ott - An Elemental Journey/src/components/EnemyAnimationController.cpp"
        "Ott - An Elemental Journey/src/components/EnemyAttack.cpp"
        "Ott - An Elemental Journey/src/components/EnemyMeleeAttack.cpp"
        "Ott - An Elemental Journey/src/components/EnemyMovement.cpp"
        "Ott - An Elemental Journey/src/components/EnemyShootingAttack.cpp"
        "Ott - An Elemental Journey/src/components/Generations.cpp"
        "Ott - An Elemental Journey/src/components/GrowVine.cpp"
        "Ott - An Elemental Journey/src/components/Health.cpp"
        "Ott - An Elemental Journey/src/components/HealthImage.cpp"
        "Ott - An Elemental Journey/src/components/ImageVine.cpp"
        "Ott - An Elemental Journey/src/components/MapComponent.cpp"
        "Ott - An Elemental Journey/src/components/PhysicsComponent.cpp"
        "Ott - An Elemental Journey/src/components/PlayerAnimationComponent.cpp"
        "Ott - An Elemental Journey/src/components/PlayerAttack.cpp"
        "Ott - An Elemental Journey/src/components/PlayerInput.cpp"
        "Ott - An Elemental Journey/src/components/SlimeAttack.cpp"
        "Ott - An Elemental Journey/src/components/SlimeStates.cpp"
        "Ott - An Elemental Journey/src/components/TestEnemyInput.cpp"
        "Ott - An Elemental Journey/src/components/earthAnimationController.cpp"
        "Ott - An Elemental Journey/src/components/EnemyContactDamage.cpp"
        "Ott - An Elemental Journey/src/components/FadeOutAnimationComponent.cpp"
        "Ott - An Elemental Journey/src/components/WaterAnimationController.cpp"
        "Ott - An Elemental Journey/src/components/EarthBossAnimationController.cpp"
        "Ott - An Elemental Journey/src/components/EarthBossAttack.cpp"
        "Ott - An Elemental Journey/src/components/EarthBossManager.cpp"
        "Ott - An Elemental Journey/src/components/EnterBossRoom.cpp"
        "Ott - An Elemental Journey/src/components/FadeTransitionComponent.cpp"
        "Ott - An Elemental Journey/src/components/Trigger.cpp"
        "Ott - An Elemental Journey/src/components/VineManager.cpp"
        "Ott - An Elemental Journey/src/components/ColliderVine.cpp"
        "Ott - An Elemental Journey/src/components/Acceleration.cpp"
        "Ott - An Elemental Journey/src/components/DamageArea.cpp"
        "Ott - An Elemental Journey/src/components/Destruction.cpp"
        "Ott - An Elemental Journey/src/components/LifeAnimationComponent.cpp"
        "Ott - An Elemental Journey/src/components/Pivot.cpp"
        "Ott - An Elemental Journey/src/components/WaterBossAnimationComponent.cpp"

        #ECS
        "Ott - An Elemental Journey/src/ecs/Manager.cpp"
        "Ott - An Elemental Journey/src/ecs/anims.cpp"
        "Ott - An Elemental Journey/src/ecs/colliders.cpp"

        #GAME
        "Ott - An Elemental Journey/src/game/Game.cpp"

        #JSON
        "Ott - An Elemental Journey/src/json/JSON.cpp"
        "Ott - An Elemental Journey/src/json/JSONValue.cpp"

        #SDLUTILS
        "Ott - An Elemental Journey/src/sdlutils/SDLUtils.cpp"
        "Ott - An Elemental Journey/src/sdlutils/Texture.cpp"
        "Ott - An Elemental Journey/src/sdlutils/SoundEffect.cpp"
        "Ott - An Elemental Journey/src/sdlutils/Music.cpp"

        #STATES
        "Ott - An Elemental Journey/src/states/GameStateMachine.cpp"
        "Ott - An Elemental Journey/src/states/PlayState.cpp"
        "Ott - An Elemental Journey/src/states/menus/MainMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/PauseMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/OptionsMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/MusicOptionsMenuState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/ControlMenuState.cpp"
        "Ott - An Elemental Journey/src/states/MapState.cpp"
        "Ott - An Elemental Journey/src/states/menus/options/GraphicsOptionsMenuState.cpp"

        #UTILS
        "Ott - An Elemental Journey/src/utils/Collisions.cpp"
        "Ott - An Elemental Journey/src/utils/Vector2D.cpp"
        )

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} "/usr/local/include")
target_link_libraries(Ott ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} "/usr/local/lib/libtmxlite.dylib")