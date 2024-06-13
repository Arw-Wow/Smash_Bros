#pragma once
#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_sun;						    			// ̫��ͼ��
extern Atlas atlas_sun_explode;					    		//̫����ըͼ��

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
        Bullet::onTouch();  //��д�Ծ�Ҫ���ø��ຯ��ʱ������������ʽ����

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
            // velocity.y = 0;  //position���Ӿ�û��ϵ��
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

    Animation animation_idle;               // Ĭ�϶���
    Animation animation_explode;            // ��ը����

    Vector2 explode_render_offset;          // ��ը������Ⱦƫ������Ĭ�϶����ͱ�ը������С��һ����Ҫ��ƫ�Ʋ��ܱ�֤���ĵ�һ�£�

	const double gravity = 0.0025;	//����

};
