#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
#include "../Src/Entity.h"
class Image : public Component {
public:
	Image(Texture* text);
	virtual ~Image();
	void initComponent() override;
	void render() override;
	inline SDL_Rect getRect() {
		return dest;
	}
	constexpr static cmpId_type id = ecs::_IMAGE;
private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect dest;
};

