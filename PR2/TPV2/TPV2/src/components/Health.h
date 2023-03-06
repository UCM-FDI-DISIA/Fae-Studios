#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include <vector>
class Health : public Component
{
private:
	int health = 0, maxHealth = 3;
	std::vector<Texture*> textures;
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	Health(Texture* t, int h) : Component() {
		maxHealth = h;
		health = h;
		for (int i = 0; i < health; ++i)
			textures.push_back(t);
	};
	virtual ~Health() = default;
	void render() override;
	void quitHealth();
	void resetHealth();
	int getHealth();
};

