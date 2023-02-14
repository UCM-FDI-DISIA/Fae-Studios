#pragma once
#include "UIElement.h"
class ChargedAttackBar : public UIElement {
private:
    int charges;

public:
    ChargedAttackBar(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) : UIElement(position, texture, scale) {
        charges = 0;
    }

    void render() const final;

    void addCharge() {++charges;}

    void resetCharges() {charges = 0;}

    void reallocate();
};

