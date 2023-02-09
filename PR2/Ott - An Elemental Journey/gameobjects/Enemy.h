#pragma once
#include "MovingObject.h"
#include "../utils/Elements.h"
#include <iostream>

// MOVER ARCHIVOS Y COLOCAR BIEN
// CLASE TEMPORAL PARA PROBAR COSAS

class Enemy : public MovingObject{
private:
	int maxLives;
	int actualLives;
	elementsInfo::elements element;
	bool dead = false;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f)): MovingObject(position, texture, dir, scale), actualLives(lives), element(elem) {
		maxLives = lives * 2;  // Representación interna doblada
		actualLives = lives * 2;
	}
	~Enemy() {

	}

	void Damage(elementsInfo::elements e) {
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) Die();
	}

	void Die() {
		dead = true;
		std::cout << "Muerto" << endl;
		// borrar o marcar booleano para borrar después
	}

	int GetLives() { return actualLives; }

	bool isDead() { return dead; }
};

