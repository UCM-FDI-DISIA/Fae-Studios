#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "HealthImage.h"
#include "PlayerAnimationComponent.h"

class Health : public Component
{
private:
	int maxLife, actualLife;
	ecs::elements elem;
	Entity* lastSanctuary = nullptr;
	int sanctuaryID;
	HealthImage* image;
	PlayerAnimationComponent* pAnim_;
	std::string lifeShardIDs = " ";
	bool dead = false;
	int numShards = 0;
	inline void increaseMaxLife() { maxLife++; actualLife = maxLife; image->increaseLife(); };

public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e, bool player = false) : Component(), elem(e) {
		if (player) { maxLife = h; actualLife = h; }
		else { maxLife = 2 * h; actualLife = 2 * h; }// La vida de los enemigos tiene una representación diferente
	};
	//Este método activa la animación
	void die();
	virtual void initComponent();
	//Este te lleva al santuario
	void recall(bool rest = false);
	inline bool isDead() { return dead; }
	inline void setDead(bool dead) { this->dead = dead; }
	bool recieveDamage(ecs::elements el, bool dir);
	inline int getHealth() { return actualLife; }
	inline int getMaxHealth() { return maxLife; }
	inline std::string getLifeShardIDs() { return lifeShardIDs; }
	inline ecs::elements getElement() { return elem; }
	inline void setElement(int newElem) {
		switch (newElem)
		{
		case 0: elem = ecs::Light; break;
		case 1: elem = ecs::Earth; break;
		case 2: elem = ecs::Water; break;
		case 3: elem = ecs::Fire; break;
		default: break;
		}
		image->changeElement(elem);
	}
	void saveSactuary(Entity* sanct);
	inline int getSanctuaryID() { return sanctuaryID; }
	inline void setSanctuary(Entity* lastS) { lastSanctuary = lastS; }
	inline void addLifeShard(int id) { numShards++; if (numShards > 1 && numShards % 2 == 0) increaseMaxLife(); 
	lifeShardIDs += (std::to_string(id) + " "); }


	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream& file);
	
};

