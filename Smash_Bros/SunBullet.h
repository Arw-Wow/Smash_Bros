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

    SunBullet();

    ~SunBullet() = default;

    void onTouch() override;

    void onUpdate(int delta) override;

    void onDraw(const Camera& camera) override;

private:

    Animation animation_idle;               // Ĭ�϶���
    Animation animation_explode;            // ��ը����

    Vector2 explode_render_offset;          // ��ը������Ⱦƫ������Ĭ�϶����ͱ�ը������С��һ����Ҫ��ƫ�Ʋ��ܱ�֤���ĵ�һ�£�

	const double gravity = 0.0025;	//����

};
