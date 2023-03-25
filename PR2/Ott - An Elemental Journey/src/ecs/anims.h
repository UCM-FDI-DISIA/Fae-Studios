#pragma once
#include <vector>
#include <array>


enum EarthBossStates { PRESENTATION, WARNING, ATTACKVERTICAL, ATTACKHORIZONTAL, PAUSE };
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
	static enum Entities { OTT_ANIM, MELEE_ANIM, RANGE_ANIM, SLIME_ANIM, EARTH_ATTACK, EARTHBOSSPRESENT, EARTHBOSSATTACK, WARNINGEARTH, PAUSE_ANIM, WATER_ATTACK, WATERBOSS_ANIM, LIFE_SHARD };
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
	static std::vector<animDescription> lifeshard_anims;
	static std::vector<animDescription> melee_anims;
	static std::vector<animDescription> range_anims;
	static std::vector<animDescription> slime_anims;
	static std::vector<animDescription> waterBoss_anims;
	static std::vector<animDescription> earth_attack;
	//ANIMACIONES RELACIONADAS CON LA BATALLA DEL BOSS DE TIERRA
	static std::vector<animDescription> earthBossPresent_anims;
	static std::vector<animDescription> earthBoss_anims;
	static std::vector<animDescription> warning_anims;
	static std::vector<animDescription> pause_anims;
	//ATAQUE AGUA
	static std::vector<animDescription> water_attack;

	static offsetPhysics ott_collider;
	static offsetPhysics melee_collider;
	static offsetPhysics range_collider;
	static offsetPhysics slime_collider;
	//static offsetPhysics earth_collider;
};