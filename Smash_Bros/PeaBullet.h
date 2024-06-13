#pragma once

#include "Bullet.h"
#include "Animation.h"

extern IMAGE img_pea;										// Õ„∂πÕº∆¨
extern Atlas atlas_pea_break;								// Õ„∂π∆∆ÀÈÕººØ



class PeaBullet :
    public Bullet
{
public:

    PeaBullet();

    ~PeaBullet() = default;

    void onTouch() override;

    void onUpdate(int delta) override;

    void onDraw(const Camera& camera) override;

private:

    IMAGE* img;
    Animation animation_break;

};
