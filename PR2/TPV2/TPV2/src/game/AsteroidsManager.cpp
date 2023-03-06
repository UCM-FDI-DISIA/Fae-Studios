#include "../utils/checkML.h"
#include "AsteroidsManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Follow.h"
#include "../ecs/Entity.h"

AsteroidsManager::AsteroidsManager(Manager* m): mngr_(m) {
    currentAsteroids_ = 0; //Inicializamos el número de asteroides a 0
    genTime = GENERATION_TIME; //Ponemos el tiempo de generación en el tiempo que hayamos estipulado
}

void AsteroidsManager::createAsteroids(int n) {
    Vector2D position;
    //Añadiremos tantos asteroides como hayamos pedido mientras que se puedan añadir
    for(int i = n; currentAsteroids_ < MAX_NUMBER_OF_ASTEROIDS && i != 0; --i) {
        currentAsteroids_++; //Sumamos un asteroide al total
        //Añadimos un asteroide al manager
        auto asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);
        int generations = sdlutils().rand().nextInt(1, 4);
        asteroid->addComponent<Generations>(generations);

        //Hacemos toda la lógica de posicionar el asteroide en los bordes de pantalla y
        //calcular su vector dirección a partir de la posición
        Vector2D screenCenter((sdlutils().width() / 2) + sdlutils().rand().nextInt(-100, 101), (sdlutils().height() / 2) + sdlutils().rand().nextInt(-100, 101));
        float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
        
        if (sdlutils().rand().nextInt(0, 10) < 5) {
            if (sdlutils().rand().nextInt(0, 10) < 5) position = Vector2D(sdlutils().rand().nextInt(0, BORDER_MARGIN), sdlutils().rand().nextInt(0, sdlutils().height()));
            else position = Vector2D(sdlutils().rand().nextInt(sdlutils().width() - BORDER_MARGIN, sdlutils().width()), sdlutils().rand().nextInt(0, sdlutils().height()));  
        }
        else {
            if (sdlutils().rand().nextInt(0, 10) < 5) position = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().rand().nextInt(0, BORDER_MARGIN));
            else position = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().rand().nextInt(sdlutils().height() - BORDER_MARGIN, sdlutils().height()));
        }
        asteroid->addComponent<Transform>(position, ((screenCenter - position).normalize()) * speed, 10.0f + 5.0f * generations, 10.0f + 5.0f * generations);

        asteroid->addComponent<ShowAtOpposideSide>();

        //Hacemos la lógica de si el asteroide va a ser dorado o no
        if(sdlutils().rand().nextInt(0,10) < 3) {
            asteroid->addComponent<Follow>();
            asteroid->addComponent<FramedImage>(&sdlutils().images().at("golden_asteroid"), 5, 6);
        }
        else asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6);
    }
}

void AsteroidsManager::addAsteroidFrequently() {
    if(SDL_GetTicks() >= genTime) { //Si tras una llamada al método se han superado los 5 segundos...
        createAsteroids(1); //añadimos un asteroide...
        genTime = SDL_GetTicks() + GENERATION_TIME; //y sumamos otros 5 segundos al tiempo total
    }
}

void AsteroidsManager::destroyAllAsteroids() {
    //Destruimos todos los asteroides poniendo en false su setAlive
    for(Entity* e : mngr_->getEntities(ecs::_grp_ASTEROIDS)) e->setAlive(false);
    currentAsteroids_ = 0;
}

void AsteroidsManager::onCollision(Entity* a){
    sdlutils().soundEffects().at("bang_large").play(0, 1); //Reproducimos el sonido de romper un asteroide
    currentAsteroids_--; //Restamos uno al número total de asteroides
    if (a->getComponent<Generations>()->getGeneration() > 1) { //Si la generación del asteroide es mayor a 1...
        if (currentAsteroids_ < 30) //Y si el número de asteroides es menor que 30...
            Divide(a); //Lo dividimos
    }
    a->setAlive(false); //Y lo destruimos
}

void AsteroidsManager::Divide(Entity* a){
    Transform* t = a->getComponent<Transform>(); //Obtenemos el transform del asteroide
    auto as1 = mngr_->addEntity(ecs::_grp_ASTEROIDS); //Añadimos un asteroide al manager
    as1->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1); //Le añadimos la generación del padre - 1
    //Ponemos su posición a partir de la posición del padre
    as1->addComponent<Transform>(t->getPosition() + t->getVelocity().rotate(t->getRotation()) * 2 * std::max(t->getWidth(), t->getHeight()), t->getVelocity().rotate(t->getRotation()) * 1.1f, 10.0f + 5.0f * 1, 10.0f + 5.0f * 1, sdlutils().rand().nextInt(0, 360));
    as1->addComponent<ShowAtOpposideSide>(); //Le añadimos el showAtOppositeSide

    //Hacemos la lógica de si el asteroide va a ser dorado o no
    if (sdlutils().rand().nextInt(0, 10) < 3) {
        as1->addComponent<Follow>();
        as1->addComponent<FramedImage>(&sdlutils().images().at("golden_asteroid"), 5, 6);
    }
    else as1->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6);

    //Sumamos uno al total de asteroides
    currentAsteroids_++;

    //Si podemos añadir un asteroide más, lo creamos exactamente igual
    if (currentAsteroids_ < 30) {
        auto as2 = mngr_->addEntity(ecs::_grp_ASTEROIDS);
        as2->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);
        as2->addComponent<Transform>(t->getPosition() + t->getVelocity().rotate(t->getRotation()) * 2 * std::max(t->getWidth(), t->getHeight()), (t->getVelocity().rotate(t->getRotation()) * 1.1f) * -1, 10.0f + 5.0f * 1, 10.0f + 5.0f * 1, sdlutils().rand().nextInt(0, 360));
        as2->addComponent<ShowAtOpposideSide>();
        if (sdlutils().rand().nextInt(0, 10) < 3) {
            as2->addComponent<Follow>();
            as2->addComponent<FramedImage>(&sdlutils().images().at("golden_asteroid"), 5, 6);
        }
        else as2->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6);
        currentAsteroids_++;
    }
}
