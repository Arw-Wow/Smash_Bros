#pragma once
#include "Player.h"
#include "PeaBullet.h"

extern Atlas atlas_peashooter_idle_left;					// 豌豆射手朝向左的闲置动画图集
extern Atlas atlas_peashooter_idle_right;					// 豌豆射手朝向右的闲置动画图集
extern Atlas atlas_peashooter_run_left;		    			// 豌豆射手朝向左的奔跑动画图集
extern Atlas atlas_peashooter_run_right;					// 豌豆射手朝向右的奔跑动画图集
extern Atlas atlas_peashooter_attack_ex_left;				// 豌豆射手朝向左的特殊攻击动画图集
extern Atlas atlas_peashooter_attack_ex_right;				// 豌豆射手朝向右的特殊攻击动画图集

extern std::vector <Bullet*> bullet_list;

class Peashooter :
    public Player
{
public:

    Peashooter()
    {
		Type = PlayerType::PeaShooter;

        // 给current animation赋初值
        animation_current = &animation_idle_right;

        animation_idle_left.setAtlas(&atlas_peashooter_idle_left);
        animation_idle_left.setInterval(100);
        animation_idle_left.setLoop(true);

        animation_idle_right.setAtlas(&atlas_peashooter_idle_right);
        animation_idle_right.setInterval(100);
        animation_idle_right.setLoop(true);

        animation_run_left.setAtlas(&atlas_peashooter_run_left);
        animation_run_left.setInterval(100);
        animation_run_left.setLoop(true);

        animation_run_right.setAtlas(&atlas_peashooter_run_right);
        animation_run_right.setInterval(100);
        animation_run_right.setLoop(true);

		animation_attack_ex_left.setAtlas(&atlas_peashooter_attack_ex_left);
		animation_attack_ex_left.setInterval(75);
		animation_attack_ex_left.setLoop(true);

		animation_attack_ex_right.setAtlas(&atlas_peashooter_attack_ex_right);
		animation_attack_ex_right.setInterval(75);
		animation_attack_ex_right.setLoop(true);



		timer_attack_ex.setOneShot(true);
		timer_attack_ex.setWaitTime(attack_ex_duration);
		timer_attack_ex.setShotCallback(
			[&]() {
				is_attacking_ex = false;
			}
		);

		timer_spawn_pea_ex.setOneShot(false);
		timer_spawn_pea_ex.setWaitTime(100);	// 特殊攻击时子弹生成间隔
		timer_spawn_pea_ex.setShotCallback(
			[&]() {
				spawn_pea_bullet(speed_pea_ex);
			}
		);

		attack_cd = 150;
		timer_attack_cd.setWaitTime(attack_cd);
    }

    ~Peashooter() = default;

    void onAttack() override
    {
        spawn_pea_bullet(speed_pea);
    }

    void onAttack_ex() override
    {
		is_attacking_ex = true;
		timer_attack_ex.restart();

		animation_attack_ex_left.reset();
		animation_attack_ex_right.reset();

		// mciSendString("play pea_shoot_ex from 0", NULL, 0, NULL);

    }

	void onUpdate(int delta) override
	{
		Player::onUpdate(delta);

		if (is_attacking_ex)
		{
			timer_attack_ex.onUpdate(delta);

			timer_spawn_pea_ex.onUpdate(delta);

			main_camera.shake(5, 100);
		}
	}

private:

    void spawn_pea_bullet(double speed)	//生成子弹（生成子弹与攻击分成两个函数，是因为特殊与普通攻击都要生成子弹，且子弹都一样，所以生成子弹单独封装成函数。sunflower就不是这样了）
    {
        Bullet* bullet = new PeaBullet();

        Vector2 bullet_velocity, bullet_position;

        const Vector2& bullet_size = bullet->getSize();

		bullet_position.y = position.y;
		bullet_velocity.y = 0;

        if (is_facing_left)
        {
            bullet_position.x = position.x - bullet_size.x / 2;
			bullet_velocity.x = -speed;
        }
        else
        {
            bullet_position.x = position.x + size.x - bullet_size.x / 2;
			bullet_velocity.x = speed;
        }

		bullet->setPosition(bullet_position.x, bullet_position.y);
		bullet->setVelocity(bullet_velocity.x, bullet_velocity.y);

		bullet->setTarget(ID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
		bullet->setTouchCallback(
			[&]() {
				mp += 25;
			}
		);

		bullet_list.push_back(bullet);	
		
		switch (rand() % 2)
		{
		case 0:
			mciSendString("play pea_shoot_1 from 0", NULL, 0, NULL);
			break;
		case 1:
			mciSendString("play pea_shoot_2 from 0", NULL, 0, NULL);
			break;
		}

    }

private:

    const double speed_pea = 0.75;          // 子弹发射速度不应该是子弹本身的属性，而应该是发射子弹的“枪”的属性，所以封装在player中。将子弹类纯粹化
    const double speed_pea_ex = 1.5;

	const int attack_ex_duration = 2500;	//特殊攻击持续时间

	Timer timer_attack_ex;	//特殊攻击状态计时器
	Timer timer_spawn_pea_ex;	//特殊攻击子弹生成计时器


};

