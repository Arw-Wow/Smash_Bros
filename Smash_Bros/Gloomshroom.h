#pragma once

#include "Player.h"
#include "BubblesBullet_ex.h"

extern Atlas atlas_gloomshroom_idle_left;					// 大喷菇向左的闲置动画图集
extern Atlas atlas_gloomshroom_idle_right;					// 大喷菇朝向右的闲置动画图集
extern Atlas atlas_gloomshroom_run_left;		    		// 大喷菇朝向左的奔跑动画图集
extern Atlas atlas_gloomshroom_run_right;					// 大喷菇朝向右的奔跑动画图集
extern Atlas atlas_gloomshroom_attack_ex_left;				// 大喷菇朝向左的特殊攻击动画图集
extern Atlas atlas_gloomshroom_attack_ex_right;				// 大喷菇朝向右的特殊攻击动画图集
extern Atlas atlas_gloomshroom_die_left;					// 大喷菇朝向左的死亡动画图集
extern Atlas atlas_gloomshroom_die_right;					// 大喷菇朝向右的死亡动画图集

class Gloomshroom :
	public Player
{
public:

	Gloomshroom();

	~Gloomshroom() = default;

	void onAttack() override;

	void onAttack_ex() override;

	void onUpdate(int delta) override;

	void spawn_bubbles_bullet();

	void spawn_bubbles_bullet_ex();

	void onRun(double distance) override;

	void onJump() override;
	
private:


	Timer timer_attack_ex;	//特殊攻击状态计时器
	Timer timer_bubbles_ex;	//特殊攻击时间间隔

	const int attack_ex_duration = 2000;	//特殊攻击持续时间

};


