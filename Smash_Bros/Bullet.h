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
		// ���ӵ��������ж�touch�������Եø���Ȼ�������Ǹ��ڱ߽�Ӵ�����touch
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
			solidcircle(position.x + size.x / 2, position.y + size.y / 2, 5);	// ��ʾ���ĵ㣨��ʵ��Բ���ⲻ���ԣ�
		}
	}


protected:

	Vector2 position;							// �ӵ�λ��
	Vector2 size;								// �ӵ���С
	Vector2 velocity;							// �ӵ��ٶ�ʸ��

	int damage = 10;							// �ӵ��˺�

	bool is_valid = true;						// �ӵ��Ƿ���Ч����������˺���
	bool can_remove = false;					// �ӵ��Ƿ����ɾ��

	PlayerID target_player_id = PlayerID::P1;					// �ӵ�Ŀ�꣨���ˣ�

	std::function < void() > touch_callback;	// �ӵ���ײ�󴥷��Ļص�����

};

