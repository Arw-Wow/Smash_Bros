#pragma once
#include "Player.h"
#include "PeaBullet.h"

extern Atlas atlas_peashooter_idle_left;					// 豌豆射手朝向左的闲置动画图集
extern Atlas atlas_peashooter_idle_right;					// 豌豆射手朝向右的闲置动画图集
extern Atlas atlas_peashooter_run_left;		    			// 豌豆射手朝向左的奔跑动画图集
extern Atlas atlas_peashooter_run_right;					// 豌豆射手朝向右的奔跑动画图集
extern Atlas atlas_peashooter_attack_ex_left;				// 豌豆射手朝向左的特殊攻击动画图集
extern Atlas atlas_peashooter_attack_ex_right;				// 豌豆射手朝向右的特殊攻击动画图集
extern Atlas atlas_peashooter_die_left;						// 豌豆射手朝向左的死亡动画图集
extern Atlas atlas_peashooter_die_right;					// 豌豆射手朝向右的死亡动画图集

extern std::vector <Bullet*> bullet_list;

class Peashooter :
    public Player
{
public:

    Peashooter();

    ~Peashooter() = default;

    void onAttack() override;

    void onAttack_ex() override;

	void onUpdate(int delta) override;

private:

    void spawn_pea_bullet(double speed);

private:

    const double speed_pea = 0.75;          // 子弹发射移动速度不应该是子弹本身的属性，而应该是发射子弹的“枪”的属性，所以封装在player中。将子弹类纯粹化
    const double speed_pea_ex = 1.5;

	const int attack_ex_duration = 2500;	//特殊攻击持续时间

	Timer timer_attack_ex;	//特殊攻击状态计时器
	Timer timer_spawn_pea_ex;	//特殊攻击子弹生成计时器


};

