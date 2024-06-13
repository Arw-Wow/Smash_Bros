#include "SunBullet.h"

SunBullet::SunBullet()
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

void SunBullet::onTouch()
{
    Bullet::onTouch();  //重写仍旧要调用父类函数时，可以这样显式调用

    is_valid = false;

    main_camera.shake(5, 250);

    mciSendString("play sun_explode from 0", NULL, 0, NULL);
}

void SunBullet::onUpdate(int delta)
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

void SunBullet::onDraw(const Camera& camera)
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
