#pragma once

#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_bubbles;


class BubblesBullet : public Bullet
{

public:

	BubblesBullet();

	~BubblesBullet() = default;

	void onTouch() override;

	void onUpdate(int delta) override;

	void onDraw(const Camera& camera) override;

	bool checkTouch(const Vector2& target_position, const Vector2& target_size) override;

	Vector2& getRenderOffset();

protected:

	Animation animation_bubbles;

	Vector2 render_offset = { -48, -48 };

};
