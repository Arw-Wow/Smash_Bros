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

	void setPosition(double x, double y)
	{
		position.x = x;
		position.y = y;
	}

	const Vector2& getPosition() const
	{
		return position;
	}

	void setSize(double x, double y)
	{
		size.x = x;
		size.y = y;
	}

	const Vector2& getSize() const
	{
		return size;
	}

	void setVelocity(double x, double y)
	{
		velocity.x = x;
		velocity.y = y;
	}

	const Vector2& getVelocity()
	{
		return velocity;
	}

	void setDamage(int val)
	{
		damage = val;
	}

	int getDamage() const
	{
		return damage;
	}

	void setTarget(PlayerID target)
	{
		target_player_id = target;
	}

	PlayerID getTarget() const
	{
		return target_player_id;
	}

	void setTouchCallback(std::function < void() > callback)
	{
		this->touch_callback = callback;
	}

	void setValid(bool in)
	{
		is_valid = in;
	}

	bool getValid() const
	{
		return is_valid;
	}

	bool checkCanRemove() const
	{
		return can_remove;
	}

	bool checkOutScreen() const
	{
		int x = (int)(position.x + size.x) / 2;
		int y = (int)(position.y + size.y) / 2;

		return (x < 0 || x > getwidth() || y < 0 || y > getheight());
	}

	virtual void onTouch()
	{
		if (touch_callback)
			touch_callback();
	}

	virtual bool checkTouch(const Vector2& target_position, const Vector2& target_size)
	{
		// 以子弹中心来判断touch，这样显得更自然，而不是刚在边界接触就算touch
		int x = (int)(position.x + size.x / 2);
		int y = (int)(position.y + size.y / 2);

		return (x > target_position.x && x < target_position.x + target_size.x && y > target_position.y && y < target_position.y + target_size.y);
	}

	virtual void onUpdate(int delta)
	{

	}

	virtual void onDraw(const Camera& camera)
	{
		if (is_debug)
		{
			setlinecolor(YELLOW);
			line_alpha(camera, position.x, position.y, position.x + size.x, position.y);
			line_alpha(camera, position.x, position.y, position.x, position.y + size.y);
			line_alpha(camera, position.x + size.x, position.y, position.x + size.x, position.y + size.y);
			line_alpha(camera, position.x, position.y + size.y, position.x + size.x, position.y + size.y);

			setfillcolor(YELLOW);
			solidcircle(position.x + size.x / 2, position.y + size.y / 2, 5);	// 显示中心点（用实心圆以免不明显）
		}
	}


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

