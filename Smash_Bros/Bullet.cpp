#include "Bullet.h"

void Bullet::setType(BulletType type)
{
	this->type = type;
}

BulletType Bullet::getType()
{
	return this->type;
}

void Bullet::setPosition(double x, double y)
{
    position.x = x;
    position.y = y;
}

const Vector2& Bullet::getPosition() const
{
    return position;
}

void Bullet::setSize(double x, double y)
{
    size.x = x;
    size.y = y;
}

const Vector2& Bullet::getSize() const
{
    return size;
}

void Bullet::setVelocity(double x, double y)
{
    velocity.x = x;
    velocity.y = y;
}

const Vector2& Bullet::getVelocity()
{
    return velocity;
}

void Bullet::setDamage(int val)
{
    damage = val;
}

int Bullet::getDamage() const
{
    return damage;
}

void Bullet::setTarget(PlayerID target)
{
    target_player_id = target;
}

PlayerID Bullet::getTarget() const
{
    return target_player_id;
}

void Bullet::setTouchCallback(std::function<void()> callback)
{
    this->touch_callback = callback;
}

void Bullet::setValid(bool in)
{
    is_valid = in;
}

bool Bullet::getValid() const
{
    return is_valid;
}

bool Bullet::checkCanRemove() const
{
    return can_remove;
}

bool Bullet::checkOutScreen() const
{
    int x = (int)(position.x + size.x) / 2;
    int y = (int)(position.y + size.y) / 2;

    return (x < 0 || x > getwidth() || y < 0 || y > getheight());
}

void Bullet::onTouch()
{
    if (touch_callback)
        touch_callback();
}

bool Bullet::checkTouch(const Vector2& target_position, const Vector2& target_size)
{
    // 以子弹中心来判断touch，这样显得更自然，而不是刚在边界接触就算touch
    int x = (int)(position.x + size.x / 2);
    int y = (int)(position.y + size.y / 2);

    return (x > target_position.x && x < target_position.x + target_size.x && y > target_position.y && y < target_position.y + target_size.y);
}

void Bullet::onUpdate(int delta)
{

}

void Bullet::onDraw(const Camera& camera)
{
    if (is_debug)
    {
        setlinecolor(YELLOW);
        line_alpha(camera, position.x, position.y, position.x + size.x, position.y);
        line_alpha(camera, position.x, position.y, position.x, position.y + size.y);
        line_alpha(camera, position.x + size.x, position.y, position.x + size.x, position.y + size.y);
        line_alpha(camera, position.x, position.y + size.y, position.x + size.x, position.y + size.y);

        setfillcolor(YELLOW);
        solidcircle(position.x + size.x / 2, position.y + size.y / 2, 5);	// 显示中心点（用实心圆以免不明显）
    }
}
