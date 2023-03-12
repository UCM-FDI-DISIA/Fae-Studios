#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"
#include "../dependencies/Texture.h"
#include "ColliderVine.h"
#include "GrowVine.h"
#include "ImageVine.h"
class VineManager: public Component
{
private:
	Texture* texture_;
	Vector2D iniPos;
	Vector2D finPos;
	int width;
	int height;
	int dir;
	int speed;
	float rotation;
	Entity* vine;
	bool hasVine = false;

public:
	constexpr static cmpId_type id = ecs::_VINEMANAGER;
	VineManager(Texture* t, Vector2D ini, Vector2D fin, int d, float r, int w, int h, int s): texture_(t), iniPos(ini), finPos(fin), dir(d), rotation(r), width(w), height(h), speed(s), vine(nullptr) {};
	virtual ~VineManager(){}
	void createVine();
	void addVine();
	inline Vector2D getIniPos() {
		return iniPos;
	}
	inline Vector2D getFinPos() {
		return finPos;
	}
	inline int getWidth() {
		return width;
	}
	inline int getHeigth() {
		return height;
	}
	inline int getDir() {
		return dir;
	}
	inline float getRotation() {
		return rotation;
	}
	inline Entity* getVine() {
		return vine;
	}
};

