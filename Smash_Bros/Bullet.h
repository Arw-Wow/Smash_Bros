#pragma once

#include <functional>
#include <graphics.h>

#include "Vector2.h"
#include "PlayerID.h"
#include "Camera.h"
#include "Tools.h"

extern bool is_debug;

class Bullet
{
public:

	Bullet() = default;

	~Bullet() = default;

	void setPosition(double x, double y);

	const Vector2& getPosition() const;

	void setSize(double x, double y);

	const Vector2& getSize() const;

	void setVelocity(double x, double y);

	const Vector2& getVelocity();

	void setDamage(int val);

	int getDamage() const;

	void setTarget(PlayerID target);

	PlayerID getTarget() const;

	void setTouchCallback(std::function < void() > callback);

	void setValid(bool in);

	bool getValid() const;

	bool checkCanRemove() const;

	bool checkOutScreen() const;

	virtual void onTouch();

	virtual bool checkTouch(const Vector2& target_position, const Vector2& target_size);

	virtual void onUpdate(int delta);

	virtual void onDraw(const Camera& camera);


protected:

	Vector2 position;							// 子弹位置
	Vector2 size;								// 子弹大小
	Vector2 velocity;							// 子弹速度矢量

	int damage = 10;							// 子弹伤害

	bool is_valid = true;						// 子弹是否有效（可以造成伤害）
	bool can_remove = false;					// 子弹是否可以删除

	PlayerID target_player_id = PlayerID::P1;					// 子弹目标（敌人）

	std::function < void() > touch_callback;	// 子弹碰撞后触发的回调函数

};

