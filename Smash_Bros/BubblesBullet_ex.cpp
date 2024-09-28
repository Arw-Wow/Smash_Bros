#include "BubblesBullet_ex.h"

BubblesBullet_ex::BubblesBullet_ex()
{
	BubblesBullet::BubblesBullet();

	animation_bubbles.setAtlas(&atlas_bubbles_ex);

	size.x = 350;
	size.y = 350;

	render_offset = { -192 + 48, -192 + 48 };
}
