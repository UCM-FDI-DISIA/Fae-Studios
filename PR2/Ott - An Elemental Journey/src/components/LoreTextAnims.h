#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"

class LoreTextAnims : public Component {
static const int ANIMCOLS = 3;
static const int ANIMROWS = 12;
public:
    LoreTextAnims(std::string id, anims::Entities e, Entity* e1);
    virtual ~LoreTextAnims() {};
    void initComponent() override {};
    void update() override;
    	
	inline int getTPerFrame() { return anims::animations[eAnims][0].tPerFrame / FRAME_ANIMATION_TIME; }
    inline int getNFrames() { return anims::animations[eAnims][0].numFrames;}
	inline int getRowNum() { return anims::animations[eAnims][0].rowNum;}
	inline int getColNum() { return anims::animations[eAnims][0].colNum;}
    constexpr static ecs::cmpId_type id = ecs::_LORE;
    inline void startAnim() { startAnimation = true; openText = true; open(); col = 0; end = false; }

private:
    void open() {
        row = ANIMROWS-1;
        timer_ = 0;
        closeText = false;
        openText = true;
    }
    void close() {
        timer_ = 0;
        openText = false;
        closeText = true;
    }
    int currentText = 1;
    bool startAnimation = false;
    bool end = false;
    bool startInput = false;
    bool openText = false;
    bool closeText = false;
    const int FRAME_ANIMATION_TIME = 5;
    int startAnimTicks;
    anims::Entities eAnims;
    FramedImage* image;
    int timer_ = 0;
    std::string ID_;
    int col = 0;
    int row = 0;
};
