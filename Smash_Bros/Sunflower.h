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

    Sunflower()
    {
		Type = PlayerType::SunFlower;

        // 给current animation赋初值
        animation_current = &animation_idle_right;

        animation_idle_left.setAtlas(&atlas_sunflower_idle_left);
        animation_idle_left.setInterval(100);
        animation_idle_left.setLoop(true);

        animation_idle_right.setAtlas(&atlas_sunflower_idle_right);
        animation_idle_right.setInterval(100);
        animation_idle_right.setLoop(true);

        animation_run_left.setAtlas(&atlas_sunflower_run_left);
        animation_run_left.setInterval(100);
        animation_run_left.setLoop(true);

        animation_run_right.setAtlas(&atlas_sunflower_run_right);
        animation_run_right.setInterval(100);
        animation_run_right.setLoop(true);

		animation_die_left.setAtlas(&atlas_sunflower_die_left);
		animation_die_left.setInterval(100);
		animation_die_left.setLoop(false);

		animation_die_right.setAtlas(&atlas_sunflower_die_right);
		animation_die_right.setInterval(200);
		animation_die_right.setLoop(false);

		animation_attack_ex_left.setAtlas(&atlas_sunflower_attack_ex_left);
		animation_attack_ex_left.setInterval(200);
		animation_attack_ex_left.setLoop(false);
		animation_attack_ex_left.set_Callback(
			[&]() {
				is_attacking_ex = false;
				is_sun_text_visible = false;
			}
		);

		animation_attack_ex_right.setAtlas(&atlas_sunflower_attack_ex_right);
		animation_attack_ex_right.setInterval(100);
		animation_attack_ex_right.setLoop(false);	
		animation_attack_ex_right.set_Callback(
			[&]() {
				is_attacking_ex = false;
				is_sun_text_visible = false;
			}
		);

		animation_sun_text.setAtlas(&atlas_sun_text);
		animation_sun_text.setInterval(100);
		animation_sun_text.setLoop(false);
		animation_sun_text.set_Callback(
			[&]() {
				is_attacking_ex = false;
				is_sun_text_visible = false;
			}
		);

		attack_cd = 350;
		timer_attack_cd.setWaitTime(attack_cd);
    }

    ~Sunflower() = default;

	void onAttack() override
	{
		Bullet* bullet = new SunBullet();

		Vector2 bullet_position, bullet_velocity;	// 临时存储设置值
		const Vector2 bullet_size = bullet->getSize();

		Player* target_player = (ID == PlayerID::P1 ? player_2 : player_1);

		// 将bullet设置到头顶
		bullet_position.y = position.y - bullet_size.y / 4;
		bullet_position.x = position.x + size.x / 2 - bullet_size.x / 2;
		
		if (is_facing_left)
		{
			bullet_velocity.x = -(velocity_sun.x);
			bullet_velocity.y = velocity_sun.y;
		}
		else
		{
			bullet_velocity.x = velocity_sun.x;
			bullet_velocity.y = velocity_sun.y;
		}

		bullet->setPosition(bullet_position.x, bullet_position.y);
		bullet->setVelocity(bullet_velocity.x, bullet_velocity.y);
		bullet->setTarget(target_player->getID());
		bullet->setTouchCallback(
			[&]() {
				mp += 35;
			}
		);

		bullet_list.push_back(bullet);
	}

	void onAttack_ex() override
	{
		is_attacking_ex = true;
		is_sun_text_visible = true;

		animation_sun_text.reset();
		animation_attack_ex_left.reset();
		animation_attack_ex_right.reset();

		Bullet* bullet = new SunBullet_ex();

		Vector2 bullet_position, bullet_velocity;
		const Vector2 bullet_size = bullet->getSize();

		Player* target_player = (ID == PlayerID::P1 ? player_2 : player_1);

		//bullet生成在target头顶屏幕外
		bullet_position.y = -(bullet_size.y);
		bullet_position.x = target_player->getPosition().x + size.x / 2 - bullet_size.x / 2;

		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;

		bullet->setPosition(bullet_position.x, bullet_position.y);
		bullet->setVelocity(bullet_velocity.x, bullet_velocity.y);
		bullet->setTarget(target_player->getID());
		bullet->setTouchCallback(
			[&]() {
				mp += 50;
			}
		);

		bullet_list.push_back(bullet);

		mciSendString("play sun_text from 0", NULL, 0, NULL);
	}

	void onUpdate(int delta) override
	{
		Player::onUpdate(delta);

		if (is_sun_text_visible)
		{
			animation_sun_text.onUpdate(delta);
		}
	}

	void onDraw(const Camera& camera) override
	{
		Player::onDraw(camera);

		if (is_sun_text_visible)
		{
			Vector2 text_position;
			int img_width = animation_sun_text.getCurrentFrame()->getwidth();
			int img_height = animation_sun_text.getCurrentFrame()->getheight();
			text_position.x = position.x + size.x / 2 - img_width / 2;
			text_position.y = position.y - img_height;
			animation_sun_text.onDraw(camera, text_position.x, text_position.y);
		}

	}



private:

	const double speed_sun_ex = 0.15;				// 特殊攻击匀速下落速度
	const Vector2 velocity_sun = { 0.4, -0.7 };	// 普通攻击抛射初速度，默认向右

	Animation animation_sun_text;
	bool is_sun_text_visible;	//是否显示


};

