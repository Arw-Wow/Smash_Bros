#pragma once
#include "Player.h"

#include "SunBullet.h"
#include "SunBullet_ex.h"

extern Atlas atlas_sunflower_idle_left;				    	// 向日葵朝向左的闲置动画图集
extern Atlas atlas_sunflower_idle_right;					// 向日葵朝向右的闲置动画图集
extern Atlas atlas_sunflower_run_left;						// 向日葵朝向左的奔跑动画图集
extern Atlas atlas_sunflower_run_right;			    		// 向日葵朝向右的奔跑动画图集
extern Atlas atlas_sunflower_attack_ex_left;				// 向日葵朝向左的特殊攻击动画图集
extern Atlas atlas_sunflower_attack_ex_right;				// 向日葵朝向右的特殊攻击动画图集
extern Atlas atlas_sunflower_die_left;						// 向日葵朝向左的死亡动画图集
extern Atlas atlas_sunflower_die_right;						// 向日葵朝向右的死亡动画图集

extern Atlas atlas_sun_text;								// “日”文本图集

extern Player* player_1;
extern Player* player_2;

class Sunflower :
    public Player
{
public:

    Sunflower();

    ~Sunflower() = default;

	void onAttack() override;

	void onAttack_ex() override;

	void onUpdate(int delta) override;

	void onDraw(const Camera& camera) override;

private:

	const double speed_sun_ex = 0.15;				// 特殊攻击匀速下落速度
	const Vector2 velocity_sun = { 0.4, -0.7 };	// 普通攻击抛射初速度，默认向右

	Animation animation_sun_text;
	bool is_sun_text_visible;	//是否显示

};

