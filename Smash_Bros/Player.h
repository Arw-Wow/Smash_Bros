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

	Player();

	~Player() = default;

	const Vector2& getPosition() const;

	const Vector2& getSize() const;

	void setPosition(int x, int y);

	void setID(PlayerID in_ID);

	PlayerID getID() const;

	void setType(PlayerType in_Type);

	PlayerType getType() const;

	void setFacingleft(bool in);

	int get_hp() const;

	void set_hp(int val);

	int get_mp() const;

	bool check_die() const;

	void set_velocity_die(double x, double y);

	virtual void onUpdate(int delta);

	virtual void onDraw(const Camera& camera);

	virtual void onInput(const ExMessage& msg);

	virtual void onRun(double distance);

	virtual void onAttack();

	virtual void onAttack_ex();

	void moveAndTouch(int delta);

	void onJump();

	void onLand();

	void make_invulnerable();

	virtual void onDie();

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
	Animation animation_die_left;
	Animation animation_die_right;
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

	bool is_die = false;

	Vector2 velocity_die = { 0, -1.5 };	// 玩家死亡后击飞速度矢量
};

