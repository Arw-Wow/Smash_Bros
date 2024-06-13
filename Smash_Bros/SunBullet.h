#pragma once
#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_sun;						    			// 太阳图集
extern Atlas atlas_sun_explode;					    		//太阳爆炸图集

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

    Animation animation_idle;               // 默认动画
    Animation animation_explode;            // 爆炸动画

    Vector2 explode_render_offset;          // 爆炸动画渲染偏移量（默认动画和爆炸动画大小不一样，要有偏移才能保证中心点一致）

	const double gravity = 0.0025;	//重力

};
