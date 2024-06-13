#pragma once
#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_sun;						    			// 太阳图集
extern Atlas atlas_sun_explode;					    		//太阳爆炸图集

extern Camera main_camera;

class SunBullet :
    public Bullet
{
public:

    SunBullet()
    {
        size.x = 96;
        size.y = 96;

        damage = 15;

        animation_idle.setAtlas(&atlas_sun);
        animation_idle.setInterval(50);
        animation_idle.setLoop(true);
        
        animation_explode.setAtlas(&atlas_sun_explode);
        animation_explode.setInterval(50);
        animation_explode.setLoop(false);
        animation_explode.set_Callback(
            [&]() {
                can_remove = true;
            }
        );

        explode_render_offset.x = (atlas_sun_explode.getImage(0)->getwidth() - atlas_sun.getImage(0)->getwidth()) / 2.0;
        explode_render_offset.y = (atlas_sun_explode.getImage(0)->getheight() - atlas_sun.getImage(0)->getheight()) / 2.0;

    }

    ~SunBullet() = default;

    void onTouch() override
    {
        Bullet::onTouch();  //重写仍旧要调用父类函数时，可以这样显式调用

        is_valid = false;

        main_camera.shake(5, 250);

        mciSendString("play sun_explode from 0", NULL, 0, NULL);
    }

    void onUpdate(int delta) override
    {
        if (is_valid)
        {
            velocity.y += gravity * delta;
            position += velocity * delta;

            animation_idle.onUpdate(delta);
        }
        else
        {
            // velocity.x = 0;
            // velocity.y = 0;  //position不加就没关系了
            animation_explode.onUpdate(delta);
        }
        
        if (checkOutScreen())
        {
            can_remove = true;
        }


    }

    void onDraw(const Camera& camera) override
    {
        if (is_valid)
        {
            animation_idle.onDraw(camera, (int)position.x, (int)position.y);
        }
        else
        {
            animation_explode.onDraw(camera, (int)(position.x - explode_render_offset.x), (int)(position.y - explode_render_offset.y));
        }

		Bullet::onDraw(camera);
    }





private:

    Animation animation_idle;               // 默认动画
    Animation animation_explode;            // 爆炸动画

    Vector2 explode_render_offset;          // 爆炸动画渲染偏移量（默认动画和爆炸动画大小不一样，要有偏移才能保证中心点一致）

	const double gravity = 0.0025;	//重力

};
