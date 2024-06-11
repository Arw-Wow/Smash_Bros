#pragma once

#include "Tools.h"
#include "Animation.h"
#include "Platform.h"
#include "PlayerID.h"
#include "PlayerType.h"
#include "Bullet.h"
#include "Particle.h"

extern bool is_debug;

extern std::vector <Platform> platform_list;
extern std::vector <Bullet*> bullet_list;
extern Atlas atlas_run_effect;								//奔跑效果图集
extern Atlas atlas_jump_effect;								//跳跃效果图集
extern Atlas atlas_land_effect;								//落地效果图集

extern Camera main_camera;

class Player
{
public:

	Player()
	{
		timer_attack_cd.setWaitTime(attack_cd);
		timer_attack_cd.setOneShot(true);
		timer_attack_cd.setShotCallback(
			[&]() {
				can_attack = true;
			}
		);

		timer_invulnerable.setWaitTime(750);
		timer_invulnerable.setOneShot(true);
		timer_invulnerable.setShotCallback(
			[&]() {
				is_invulnerable = false;
			}
		);

		timer_invulnerable_blink.setWaitTime(75);
		timer_invulnerable_blink.setOneShot(false);
		timer_invulnerable_blink.setShotCallback(
			[&]() {
				is_showing_white_frame = !is_showing_white_frame;
			}
		);

		timer_run_effect_generation.setWaitTime(75);
		timer_run_effect_generation.setOneShot(false);
		timer_run_effect_generation.setShotCallback(
			[&]() {
				Vector2 particle_position;
				IMAGE* frame = atlas_run_effect.getImage(0);
				particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				particle_position.y = position.y + size.y - frame->getheight();
				particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
			}
		);

		timer_die_effect_generation.setWaitTime(35);
		timer_die_effect_generation.setOneShot(false);
		timer_die_effect_generation.setShotCallback(
			[&]() {
				Vector2 particle_position;
				IMAGE* frame = atlas_run_effect.getImage(0);
				particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				particle_position.y = position.y + size.y - frame->getheight();
				particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
			}
		);

		animation_jump_effect.setAtlas(&atlas_jump_effect);
		animation_jump_effect.setInterval(25);
		animation_jump_effect.setLoop(false);
		animation_jump_effect.set_Callback(
			[&]() {
				is_jump_effect_visible = false;
			}
		);

		animation_land_effect.setAtlas(&atlas_land_effect);
		animation_land_effect.setInterval(50);
		animation_land_effect.setLoop(false);
		animation_land_effect.set_Callback(
			[&]() {
				is_land_effect_visible = false;
			}
		);
	}

	~Player() = default;

	const Vector2& getPosition() const
	{
		return position;
	}

	void setPosition(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	void setID(PlayerID in_ID)
	{
		ID = in_ID;
	}

	PlayerID getID() const
	{
		return ID;
	}

	void setType(PlayerType in_Type)
	{
		Type = in_Type;
	}

	PlayerType getType() const
	{
		return Type;
	}

	void setFacingleft(bool in)
	{
		is_facing_left = in;
	}

	int get_hp() const
	{
		return hp;
	}

	int get_mp() const
	{
		return mp;
	}

	virtual void onUpdate(int delta)
	{
		int direction = is_right_btn_down - is_left_btn_down;

		if (direction != 0)
		{
			if (!is_attacking_ex)
				is_facing_left = (direction < 0);

			if (direction < 0)
			{
				animation_current = &animation_run_left;
			}
			else
			{
				animation_current = &animation_run_right;
			}

			double distance = direction * run_velocity * delta;
			onRun(distance);
		}
		else //direction == 0
		{
			animation_current = is_facing_left ? &animation_idle_left : &animation_idle_right;
			timer_run_effect_generation.pause();	// 不动就不产生粒子
		}

		if (is_attacking_ex)
		{
			animation_current = is_facing_left ? &animation_attack_ex_left : &animation_attack_ex_right;
		}

		animation_current->onUpdate(delta);
		animation_jump_effect.onUpdate(delta);
		animation_land_effect.onUpdate(delta);

		moveAndTouch(delta);

		timer_attack_cd.onUpdate(delta);
		timer_invulnerable.onUpdate(delta);
		timer_invulnerable_blink.onUpdate(delta);
		timer_run_effect_generation.onUpdate(delta);

		if (hp <= 0)
		{
			timer_die_effect_generation.onUpdate(delta);
		}

		for (int i = 0; i < particle_list.size(); i++)
		{
			if (!(particle_list[i].check_valid()))
			{
				std::swap(particle_list[i], particle_list.back());
				particle_list.pop_back();
			}
			else
			{
				particle_list[i].on_update(delta);
			}
		}

		if (is_showing_white_frame)
		{
			white_image(animation_current->getCurrentFrame(), &img_white);
		}

	}

	virtual void onDraw(const Camera& camera)
	{
		if (is_jump_effect_visible)
		{
			animation_jump_effect.onDraw(camera, position_jump_effect.x, position_jump_effect.y);
		}
		if (is_land_effect_visible)
		{
			animation_land_effect.onDraw(camera, position_land_effect.x, position_land_effect.y);
		}

		for (const Particle& particle : particle_list)
		{
			particle.on_draw(camera);
		}
		
		if (is_invulnerable && is_showing_white_frame)
		{
			putimage_alpha(camera, position.x, position.y, &img_white);
		}
		else
		{
			animation_current->onDraw(camera, (int)position.x, (int)position.y);
		}

		if (is_debug)
		{
			setlinecolor(YELLOW);
			line_alpha(camera, position.x, position.y, position.x + size.x, position.y);
			line_alpha(camera, position.x, position.y, position.x, position.y + size.y);
			line_alpha(camera, position.x + size.x, position.y, position.x + size.x, position.y + size.y);
			line_alpha(camera, position.x, position.y + size.y, position.x + size.x, position.y + size.y);
		}
	}

	virtual void onInput(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (ID)	
			{
			case PlayerID::P1:
				switch (msg.vkcode)	
				{
				case 0x41:	//'A'
					is_left_btn_down = true;
					break;
				case 0x44:	//'D'
					is_right_btn_down = true;
					break;
				case 0x57:	//'W'
					onJump();
					break;
				case 0x46:	//'F'
					if (can_attack)
					{
						onAttack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case 0x47:	//'G'
					if (mp >= 100)
					{
						onAttack_ex();
						mp = 0;
					}
					break;
				}
				break;

			case PlayerID::P2:
				switch (msg.vkcode)	
				{
				case VK_LEFT:	//'←'
					is_left_btn_down = true;
					break;
				case VK_RIGHT:	//'→'
					is_right_btn_down = true;
					break;
				case VK_UP:		//'↑'
					onJump();
					break;
				case VK_OEM_PERIOD:	//'.'
					if (can_attack)
					{
						onAttack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case VK_OEM_2:	//'/'
					if (mp >= 100)
					{
						onAttack_ex();
						mp = 0;
					}
					break;

				}
				break;
			}
			break;

		case WM_KEYUP:
			switch (ID)
			{
			case PlayerID::P1:
				switch (msg.vkcode)	
				{
				case 0x41:	//'A'
					is_left_btn_down = false;
					break;
				case 0x44:	//'D'
					is_right_btn_down = false;
					break;
				}
				break;

			case PlayerID::P2:
				switch (msg.vkcode)	
				{
				case VK_LEFT:	//'←'
					is_left_btn_down = false;
					break;
				case VK_RIGHT:	//'→'
					is_right_btn_down = false;
					break;
				}
				break;
			}
			break;
		}
	}

	virtual void onRun(double distance)
	{
		if (is_attacking_ex)
			return;

		position.x += distance;
		timer_run_effect_generation.resume();
	}

	virtual void onAttack()
	{

	}

	virtual void onAttack_ex()
	{

	}

	void moveAndTouch(int delta)
	{
		double last_y = position.y;
		double last_velocity_y = velocity.y;

		// 模拟重力
		velocity.y += gravity * delta;	//v = v0 + at
		position += velocity * (double)delta;	//y = y0 + vt
		//这里用向量运算而不是y方向的标量运算，这样可以在速度不垂直向下的时候依旧有效。（通用性）

		for (Platform& platform : platform_list)
		{
			int left = (int)platform.getLeft();
			int right = (int)platform.getRight();
			int y = (int)platform.getY();


			if (velocity.y > 0)	//玩家下坠时才判断
			{
				if (last_y + size.y <= y && position.x < right && position.x + size.x > left && position.y <= y && position.y + size.y >= y)
				{
					// velocity = 0;
					velocity.y = 0;	// 碰到平台，y速度置0
					position.y = y - size.y;

					if (last_velocity_y != 0)
						onLand();

					break;
				}
			}
		}
		if (!is_invulnerable)	//非无敌状态才能碰撞
		{
			for (Bullet* bullet : bullet_list)
			{
				// 如果没失效或者子弹目标不是自己，就跳过
				if (!(bullet->getValid()) || bullet->getTarget() != ID)
					continue;

				if (bullet->checkTouch(position, size))
				{
					bullet->onTouch();
					bullet->setValid(false);
					hp -= bullet->getDamage();
					make_invulnerable();
				}
			}
		}
	}

	void onJump()
	{
		is_jump_effect_visible = true;
		animation_jump_effect.reset();

		IMAGE* effect_frame = animation_jump_effect.getCurrentFrame();

		position_jump_effect.x = position.x + size.x / 2 - effect_frame->getwidth() / 2;
		position_jump_effect.y = position.y + size.y - effect_frame->getheight();

		if (is_attacking_ex)	//特殊攻击禁止移动
			return;

		if (velocity.y != 0)	//防止重复跳跃
			return;

		velocity += jump_velocity;
	}

	void onLand()
	{
		is_land_effect_visible = true;
		animation_land_effect.reset();

		IMAGE* effect_frame = animation_land_effect.getCurrentFrame();

		position_land_effect.x = position.x + size.x / 2 - effect_frame->getwidth() / 2;
		position_land_effect.y = position.y + size.y - effect_frame->getheight();

	}

	void make_invulnerable()
	{
		is_invulnerable = true;
		timer_invulnerable.restart();
		// timer_invulnerable_blink.restart();	// 其实程序一直在加载闪白，只是通过is_showing布尔变量来控制是否显示处闪白效果而已
	}

protected:

	int hp = 100;
	int mp = 0;

	Vector2 position;
	Vector2 size = { 96, 96 };

	const double run_velocity = 0.55;	//水平移动速度
	const Vector2 jump_velocity = { 0, -1.0 };	//跳跃初速度矢量

	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;
	Animation animation_jump_effect;
	Animation animation_land_effect;

	bool is_jump_effect_visible = false;
	bool is_land_effect_visible = false;

	Vector2 position_jump_effect;
	Vector2 position_land_effect;

	Animation* animation_current = nullptr;

	bool is_left_btn_down = false;
	bool is_right_btn_down = false;

	PlayerID ID = PlayerID::P1;
	PlayerType Type = PlayerType::PeaShooter;

	bool is_facing_left = false;

	const double gravity = 0.0025;	//重力
	Vector2 velocity = { 0 };	//玩家速度矢量

	bool can_attack = true;		// 是否可以攻击（有cd）
	int attack_cd = 500;		// 攻击cd
	Timer timer_attack_cd;		// 攻击cd计时器

	bool is_attacking_ex = false;	// 是否正在释放特殊攻击

	bool is_invulnerable = false;	// 是否 处于无敌状态
	bool is_showing_white_frame;	// 当前帧是否可以播放闪白
	Timer timer_invulnerable;		// 无敌状态定时器（无敌总时长计时器）
	Timer timer_invulnerable_blink;	// 闪白闪烁计时器（每一段时间shot闪一次）
	IMAGE img_white;				// 闪白图片

	std::vector<Particle> particle_list;	// 粒子对象列表

	Timer timer_run_effect_generation;	// 奔跑粒子效果发射定时器
	Timer timer_die_effect_generation;	// 死亡粒子效果发射定时器
};

