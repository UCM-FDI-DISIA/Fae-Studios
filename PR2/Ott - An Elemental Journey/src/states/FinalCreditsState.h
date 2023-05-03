#pragma once
#include "GameState.h"
#include "../ecs/Entity.h"
#include<stack>
class FinalCreditsState : public GameState
{
	const int NEXT_NAME = 500;
	const SDL_Color white{ 255, 255, 255 };
	const SDL_Color transparent{ 255,255,255,1 };
private:
	std::stack<std::string> names;
	int timer;
	Entity* endText;
	bool end = false;
	Vector2D speed;

	void createNextName();
	void namesManager();
public:
	FinalCreditsState();
	~FinalCreditsState() override = default;

	void update() override;
	void handleInput() override;
};

