#include "PeaBullet.h"

PeaBullet::PeaBullet()
{
	size.x = 64;
	size.y = 64;

	damage = 8;

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

void PeaBullet::onTouch()
{
	Bullet::onTouch();  //��д�Ծ�Ҫ���ø��ຯ��ʱ������������ʽ����

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

void PeaBullet::onUpdate(int delta)
{
	position += velocity * (double)delta;

	// ����Ѿ�ʧЧ����һ��update break��animation
	if (!is_valid)
		animation_break.onUpdate(delta);

	if (checkOutScreen())
		can_remove = true;
}

void PeaBullet::onDraw(const Camera& camera)
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
