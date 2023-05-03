#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "HealthImage.h"
#include "BossHealthBar.h"
#include "PlayerAnimationComponent.h"
#include "ChargedAttackBar.h"

class Health : public Component
{
private:
	int maxLife, actualLife;
	ecs::elements elem;
	int sanctuaryID = -1;
	HealthImage* image;
	BossHealthBar* bar = nullptr;
	PlayerAnimationComponent* pAnim_;
	std::string lifeShardIDs = " ";
	bool dead = false, inmune = false;
	int numShards = 0;
	inline void increaseMaxLife() { maxLife++; actualLife = maxLife; image->increaseLife(); };

public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e, bool player = false, bool i = false) : Component(), elem(e), inmune(i) { // ENEMIGOS
		maxLife = 2 * h; actualLife = 2 * h; 
	};

	Health(int h, ecs::elements e, HealthImage* image, bool i = false) : Component(), elem(e), image(image), inmune(i) { // JUGADOR
		maxLife = h; actualLife = h;
	};

	Health(BossHealthBar* bar_, int h, ecs::elements e, bool player = false, bool i = false) : Component(), elem(e), inmune(i) {
		bar = bar_;
		bar->setBossLife(h);
		if (player) { maxLife = h; actualLife = h; }
		else { maxLife = 2 * h; actualLife = 2 * h; }// La vida de los enemigos tiene una representaci�n diferente
	};
	//Este m�todo activa la animaci�n
	void die();
	virtual void initComponent();
	//Este te lleva al santuario
	void recall(bool rest = false);
	inline bool isDead() { return dead; }
	inline void setDead(bool dead) { this->dead = dead; }
	bool recieveDamage(ecs::elements el, bool dir);
	inline int getHealth() { return actualLife; }
	inline int getMaxHealth() { return maxLife; }
	inline void resetHealth() { actualLife = maxLife; }
	inline void setHealth(int health) { actualLife = health; }
	inline std::string getLifeShardIDs() { return lifeShardIDs; }
	inline ecs::elements getElement() { return elem; }
	inline void setNewInitialPos(Vector2D newPos) {
		sanctuaryID = -1;
		ent_->getComponent<Transform>()->setInitialPosition(newPos);
	}
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
	inline void setSanctuaryID(int ID) { sanctuaryID = ID; }
	inline void addLifeShard(int id) { numShards++; if (numShards > 1 && numShards % 2 == 0) increaseMaxLife();
	lifeShardIDs += (std::to_string(id) + " "); }
	inline int getNumShards() const { return numShards; }
	inline void killHealth() { actualLife = 0; image->die(); die(); }
	inline void setInmune(bool v) { inmune = v; }
	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream& file);
};

