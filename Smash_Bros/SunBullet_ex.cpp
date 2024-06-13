#include "SunBullet_ex.h"

SunBullet_ex::SunBullet_ex()
{
    size.x = 288;
    size.y = 288;

    damage = 35;

    animation_idle.setAtlas(&atlas_sun_ex);
    animation_idle.setInterval(50);
    animation_idle.setLoop(true);

    animation_explode.setAtlas(&atlas_sun_ex_explode);
    animation_explode.setInterval(50);
    animation_explode.setLoop(false);
    animation_explode.set_Callback(
        [&]() {
            can_remove = true;
        }
    );

    explode_render_offset.x = (atlas_sun_ex_explode.getImage(0)->getwidth() - atlas_sun_ex.getImage(0)->getwidth());
    explode_render_offset.y = (atlas_sun_ex_explode.getImage(0)->getheight() - atlas_sun_ex.getImage(0)->getheight());

}

void SunBullet_ex::onTouch()
{
    Bullet::onTouch();

    is_valid = false;

    main_camera.shake(20, 350);

    mciSendString("play sun_explode_ex from 0", NULL, 0, NULL);
}

void SunBullet_ex::onUpdate(int delta)
{
    if (is_valid)
    {
        position += velocity * delta;

        animation_idle.onUpdate(delta);
    }
    else
    {
        animation_explode.onUpdate(delta);
    }

    if (checkOutScreen())
    {
        can_remove = true;
    }
}

void SunBullet_ex::onDraw(const Camera& camera)
{
    if (is_valid)
    {
        animation_idle.onDraw(camera, (int)position.x, (int)position.y);
    }
    else
    {
        animation_explode.onDraw(camera,
            (int)(position.x - explode_render_offset.x),
            (int)(position.y - explode_render_offset.y));
    }

    Bullet::onDraw(camera);
}

bool SunBullet_ex::checkTouch(const Vector2& target_position, const Vector2& target_size)
{
    return (position.x + size.x > target_position.x &&
        position.x < target_position.x + target_size.x &&
        position.y + size.y > target_position.y &&
        position.y < target_position.y + target_size.y);
}
