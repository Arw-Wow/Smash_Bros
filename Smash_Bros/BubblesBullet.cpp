#include "BubblesBullet.h"

BubblesBullet::BubblesBullet()
{
	size.x = 190;
	size.y = 190;

	damage = 20;

	animation_bubbles.setAtlas(&atlas_bubbles);
	animation_bubbles.setInterval(100);
	animation_bubbles.setLoop(false);

}

void BubblesBullet::onTouch()
{
    Bullet::onTouch();  //重写仍旧要调用父类函数时，可以这样显式调用

}

void BubblesBullet::onUpdate(int delta)
{
	animation_bubbles.onUpdate(delta);
	if (animation_bubbles.checkFinished())
		this->can_remove = true;
}

void BubblesBullet::onDraw(const Camera& camera)
{
	animation_bubbles.onDraw(camera, (int)position.x, (int)position.y);

    Bullet::onDraw(camera);
}

bool BubblesBullet::checkTouch(const Vector2& target_position, const Vector2& target_size)
{
	return (this->position.x < target_position.x + target_size.x && this->position.x + this->size.x - 40 > target_position.x &&
			this->position.y < target_position.y + target_size.y && this->position.y + this->size.y - 40 > target_position.y);
}

Vector2& BubblesBullet::getRenderOffset()
{
	return render_offset;
}
