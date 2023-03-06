#pragma once
#include "../utils/checkML.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include"../components/Image.h"
#include"../components/FighterCtrl.h"
#include"../components/DeAcceleration.h"
#include"../components/Health.h"
#include"../components/Gun.h"
#include "../components/ShowAtOpposideSide.h"
#include "PlayState.h"
#include "../states/GameStateMachine.h"
#include "../states/EndOfRoundState.h"
#include "../states/EndState.h"
#include "../states/PauseState.h"
#include "../states/WinState.h"

PlayState::PlayState() : GameState(ecs::_state_PLAY) {
    //Creamos el asteroidsManager y la nave
    asteroidsManager = new AsteroidsManager(mngr_);
    auto ship = mngr_->addEntity();
    ship->addComponent<Transform>(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(0, 0), 50, 50);
    ship->addComponent<Image>(&sdlutils().images().at("fighter2"));
    ship->addComponent<FighterCtrl>();
    ship->addComponent<DeAcceleration>();
    ship->addComponent<Health>(&sdlutils().images().at("heart"), 3);
    ship->addComponent<ShowAtOpposideSide>();
    ship->addComponent<Gun>();
}

PlayState::~PlayState() {
    delete asteroidsManager;
}

void PlayState::initAfterFreeze() {
    //Bloqueamos la entrada de teclado y generamos 10 asteroides
    blockKeyboardInputAfterUnfreeze();
    asteroidsManager->createAsteroids(10);
}

void PlayState::blockKeyboardInputAfterUnfreeze() {
    doNotDetectKeyboardInput = true;
}

void PlayState::handleInput() {
    GameState::handleInput();

    if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp()) doNotDetectKeyboardInput = false;
    if (!doNotDetectKeyboardInput) {
        if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
            GameStateMachine::instance()->pushState(new PauseState);
        }
    }
   
}


void PlayState::update() {
    GameState::update();
    checkCollisions();
    asteroidsManager->addAsteroidFrequently();
}

void PlayState::checkCollisions() {
    //Nos gurdamos los asteroides, las balas y la nave
    vector<Entity*> ast = mngr_->getEntities(ecs::_grp_ASTEROIDS);
    vector<Entity*> bull = mngr_->getEntities(ecs::_grp_BULLETS);
    Entity* player = mngr_->getEntities(ecs::_grp_GENERAL)[0];
    for (int i = 0; i < ast.size(); ++i) {
        //Comprobamos colisión entre jugador y asteroides
        if (Collisions::collidesWithRotation(player->getComponent<Transform>()->getPosition(), player->getComponent<Transform>()->getWidth(), player->getComponent<Transform>()->getHeight(), player->getComponent<Transform>()->getRotation(),
            ast[i]->getComponent<Transform>()->getPosition(), ast[i]->getComponent<Transform>()->getWidth(), ast[i]->getComponent<Transform>()->getHeight(), ast[i]->getComponent<Transform>()->getRotation())) {
            sdlutils().soundEffects().at("explosion1").play(0, 0);
            asteroidsManager->destroyAllAsteroids(); //Destruimos los asteroides
            for (Entity*& e : bull) e->setAlive(false); //Destruimos las balas
            player->getComponent<Health>()->quitHealth(); //Quitamos la vida
            //Llevamos al jugador al medio de la pantalla
            player->getComponent<Transform>()->setPosition(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
            player->getComponent<Transform>()->setRotation(360 - player->getComponent<Transform>()->getRotation());
            player->getComponent<Transform>()->setVelocity(Vector2D(0, 0));

            //Hacemos la lógica de fin de ronda o fin de partida
            if (player->getComponent<Health>()->getHealth() > 0) GameStateMachine::instance()->pushState(new EndOfRoundState());
            else GameStateMachine::instance()->pushState(new EndState());
        }

        //Comprobamos colisión entre bala y asteroides
        int j = 0;
        while (j < bull.size() && !Collisions::collides(ast[i]->getComponent<Transform>()->getPosition(), ast[i]->getComponent<Transform>()->getWidth(), ast[i]->getComponent<Transform>()->getHeight(), bull[j]->getComponent<Transform>()->getPosition(), bull[j]->getComponent<Transform>()->getWidth(), bull[j]->getComponent<Transform>()->getHeight())) j++;
        if (j < bull.size()) {
            bull[j]->setAlive(false);
            asteroidsManager->onCollision(ast[i]);
            //Si no hay más asteroides, lanzamos la condición de victoria
            if (asteroidsManager->numberOfAsteroids() == 0) GameStateMachine::instance()->pushState(new WinState()); 
        }
    }
}
