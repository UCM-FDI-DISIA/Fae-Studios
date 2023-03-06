#pragma once
#ifndef TPV2_ASTEROIDSMANAGER_H
#define TPV2_ASTEROIDSMANAGER_H
#include "../ecs/Manager.h"

const int MAX_NUMBER_OF_ASTEROIDS = 30; ///< Número máximo de asteroides en pantalla
const int GENERATION_TIME = 5000; ///< Tiempo de generación de cada asteroide en milisegundos
const int BORDER_MARGIN = 50; ///< Márgenes de los bordes de pantalla donde pueden generarse los asteroides

/// Clase que se encarga del manejo de la creación, destrucción, colisión, etc... de los asteroides
class AsteroidsManager {
private:
    int currentAsteroids_; ///< Número de asteroides en pantalla
    float genTime; ///< Variable que se guarda el tiempo que ha pasado desde la generación de un asteroide
    Manager* mngr_; ///< Puntero al manager

    /// Ejecuta la división de los asteroides
    /// \param a Entidad correspondiente al asteroide que hay que dividir
    void Divide(Entity* a);

public:
    /// Constructora de AsteroidsManager
    /// \param m Puntero al Manager que contendrá todos los asteroides creados por AsteroidsManager
    AsteroidsManager(Manager* m);

    /// Crea un asteroide en una posición aleatoria, con una velocidad aleatoria y con una generación aleatoria,
    /// que se dirige hacia el centro de la pantalla
    /// \param n Número de asteroides a generar
    void createAsteroids(int n);

    /// Añade un asteroide en pantalla cada 5 segundos
    void addAsteroidFrequently();

    /// Destruye todos los asteroides en pantalla
    void destroyAllAsteroids();

    /// Ejecuta toda la lógica de colisión entre una bala y el asteroide
    /// \param a Asteroide a comprobar
    void onCollision(Entity* a);

    /// Devuelve el número de asteroides totales en pantalla
    /// \return Entero con el número total de asteroides
    int numberOfAsteroids() const { return currentAsteroids_; }
};
#endif //TPV2_ASTEROIDSMANAGER_H
