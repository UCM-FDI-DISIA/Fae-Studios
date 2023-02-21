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
		SDL_Rect rect;
		rect.x = tr_->getPos().getX(); rect.y = tr_->getPos().getY();
		rect.w = tex_->getW(); rect.h = tex_->getH();
		return rect;
	}
	constexpr static cmpId_type id = ecs::_IMAGE;
private:
	Transform* tr_;
	Texture* tex_;
};

