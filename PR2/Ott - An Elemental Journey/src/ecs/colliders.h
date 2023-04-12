#pragma once
#include <vector>
#include <array>

class colliders
{
public:
	class offsetPhysics {
	public:
		offsetPhysics(int izqPixels, int totalHorPixels, int upPixels, int totalVertPixels, int width, int height) :
			izqPixels(izqPixels), totalHorPixels(totalHorPixels), upPixels(upPixels), totalVertPixels(totalVertPixels), width(width), height(height) {}
		int izqPixels, totalHorPixels, upPixels, totalVertPixels, width, height;
	};
	static enum Colliders { OTT, MELEE, RANGE, SLIME, WATERBOSS};
	static std::vector<offsetPhysics> collider;

private:
	static offsetPhysics ott_collider;
	static offsetPhysics melee_collider;
	static offsetPhysics range_collider;
	static offsetPhysics slime_collider;
	static offsetPhysics waterBoss_collider;
};

