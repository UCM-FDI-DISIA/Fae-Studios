#pragma once
#include <vector>
#include <array>

class anims {

public:
	class animDescription {
	public:
		animDescription(int tPerFrame, int numFrames, int rowNum, int colNum) : tPerFrame(tPerFrame), numFrames(numFrames), rowNum(rowNum), colNum(colNum) {}
		int tPerFrame;
		int numFrames;
		int rowNum;
		int colNum = 0;
	};
	static enum Entities { OTT_ANIM, MELEE_ANIM, RANGE_ANIM, SLIME_ANIM, EARTH_ANIM };
	static std::vector<std::vector<animDescription>> animations;

	class offsetPhysics {
	public:
		offsetPhysics(int izqPixels, int totalHorPixels, int upPixels, int totalVertPixels, int width, int height) : 
			izqPixels(izqPixels), totalHorPixels(totalHorPixels), upPixels(upPixels), totalVertPixels(totalVertPixels), width(width), height(height) {}
		int izqPixels, totalHorPixels, upPixels, totalVertPixels, width, height;
	};
	static enum Colliders { OTT, MELEE, RANGE, SLIME};
	static std::vector<offsetPhysics> colliders;
private:
	static std::vector<animDescription> ott_anims;
	static std::vector<animDescription> melee_anims;
	static std::vector<animDescription> range_anims;
	static std::vector<animDescription> slime_anims;
	static std::vector<animDescription> earth_anims;

	static offsetPhysics ott_collider;
	static offsetPhysics melee_collider;
	static offsetPhysics range_collider;
	static offsetPhysics slime_collider;
	//static offsetPhysics earth_collider;

};