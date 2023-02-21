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
	constexpr static cmpId_type id = ecs::_IMAGE;
private:
	Transform* tr_;
	Texture* tex_;
};

