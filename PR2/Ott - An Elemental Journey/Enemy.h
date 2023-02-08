#pragma once
#include "gameobjects/GameObject.h"
#include "Elements.h"

// MOVER ARCHIVOS Y COLOCAR BIEN
// CLASE TEMPORAL PARA PROBAR COSAS

class Enemy : public GameObject{
private:
	int maxLives;
	int actualLives;
	elementsInfo::elements element = elementsInfo::Earth;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, const Scale& scale = Scale(1.0f, 1.0f)): GameObject(position, texture, scale), actualLives(lives), element(elem) {
		maxLives = lives * 2;  // Representación interna doblada
		actualLives = lives * 2;
	}

	void Damage(elementsInfo::elements e) {
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) Die();
	}

	void Die() {
		// borrar o marcar booleano para borrar después
	}

	int GetLives() return actualLives;
};

