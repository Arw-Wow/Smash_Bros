#pragma once
#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_sun_ex;									//����̫��ͼ��
extern Atlas atlas_sun_ex_explode;							//����̫����ըͼ��

extern Camera main_camera;

class SunBullet_ex :
	public Bullet
{
public:

	SunBullet_ex();

	~SunBullet_ex() = default;

	void onTouch() override;

	void onUpdate(int delta) override;

	void onDraw(const Camera& camera) override;

	bool checkTouch(const Vector2& target_position, const Vector2& target_size) override;

private:

	Animation animation_idle;				// Ĭ�϶���
	Animation animation_explode;			// ��ը����

	Vector2 explode_render_offset;			// ��ը��Ⱦƫ��

};

