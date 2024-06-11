#pragma once

#include "Bullet.h"
#include "Animation.h"

extern IMAGE img_pea;										// 豌豆图片
extern Atlas atlas_pea_break;								// 豌豆破碎图集



class PeaBullet :
    public Bullet
{
public:

    PeaBullet()
    {
        size.x = 64;
        size.y = 64;

        damage = 10;

        img = &img_pea;
        animation_break.setAtlas(&atlas_pea_break);
        animation_break.setInterval(100);
        animation_break.setLoop(false);
        animation_break.set_Callback(
            [&]() {
                can_remove = true;
            }
        );
    }

    ~PeaBullet() = default;

    void onTouch() override
    {
        Bullet::onTouch();  //重写仍旧要调用父类函数时，可以这样显式调用

        switch (rand() % 3)
        {
        case 0:
            mciSendString("play pea_break_1 from 0", NULL, 0, NULL);
            break;
        case 1:
            mciSendString("play pea_break_2 from 0", NULL, 0, NULL);
            break;
        case 2:
            mciSendString("play pea_break_3 from 0", NULL, 0, NULL);
            break;
        }
    }

    void onUpdate(int delta) override
    {
        position += velocity * (double)delta;

        // 如果已经失效，就一致update break的animation
        if (!is_valid)
            animation_break.onUpdate(delta);

        if (checkOutScreen())
            can_remove = true;
    }

    void onDraw(const Camera& camera) override
    {
        if (is_valid)
        {
            putimage_alpha(camera, (int)position.x, (int)position.y, img);
        }
        else
        {
            animation_break.onDraw(camera, (int)position.x, (int)position.y);
        }

		Bullet::onDraw(camera);
    }





private:

    IMAGE* img;
    Animation animation_break;


};
