#pragma once
#include "ecs.h"
#include "Manager.h"/
#include "../componentes/Component.h"
#include "../utils/Elements.h"
#include <array>
#include <vector>
#include <bitset>

using namespace std;
using cmpId_type = uint8_t;
using grpId_type = uint8_t;
class Entity
{
public:
	Entity() : mngr_(nullptr), cmps_(), currCmps_(), alive_()
	{
		currCmps_.reserve(ecs::maxComponentId);
	}
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}
	inline void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	inline bool isAlive() { return alive_; }
	inline void setAlive(bool alive) { alive_ = alive; }
	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++) currCmps_[i]->update();
	}
	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++) currCmps_[i]->render();
	}
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& ...args) {
		constexpr cmpId_type cId = T::id;
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent<T>();
		currCmps_.push_back(c);
		cmps_[cId] = c;
		c->setContext(this, mngr_);
		c->initComponent();
		return c;
	}
	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;
		if (cmps_[cId] != nullptr) {
			auto iter = find(currCmps_.begin(), currCmps_.end(), cmps_[cId]);
			currCmps_.erase(iter);
			delete cmps_[cId];
			cmps_[cId] = nullptr;
		}
	}
	template<typename T>
	inline T* getComponent() {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(cmps_[cId]);
	}
	template<typename T>
	inline bool hasComponent() {
		constexpr cmpId_type cId = T::id;
		return cmps_[cId] != nullptr;
	}
public:

	void useGravity() {
		//speed = Vector2D(speed.getX(), speed.getY() + game->Gravity());
	}

	bool isGrounded(){ return ground; }

	//PlayState* getState() { return game; }
	virtual bool recieveDamage(ecs::elements elem) {
		int damageNum = elementsInfo::ottMatrix[elem][currentElement];
		if (damageNum != -1) {
			life -= damageNum;
			if (life <= 0) {
				life = 0; die();
			}
		}
		return dead;
	}
	inline void resetLives() { life = maxLife; }
	inline void addLive() { ++maxLife; }
	inline void subLive() { if (life == maxLife) --life; maxLife--; }
	inline int getCurrentElement() { return currentElement; }
	//virtual void deleteMyself() { game->deleteObject(this); }
private:
	bool alive_;
	Manager* mngr_;
	vector<Component*> currCmps_;
	array<Component*, ecs::maxComponentId> cmps_;

	uint life, maxLife;
	//PlayState* game;
	elementsInfo::elements currentElement;
	virtual void die() { dead = true; }
	Vector2D speed;
	bool ground = false;
	bool dead = false;
};

