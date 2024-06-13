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

	Vector2 position;							// �ӵ�λ��
	Vector2 size;								// �ӵ���С
	Vector2 velocity;							// �ӵ��ٶ�ʸ��

	int damage = 10;							// �ӵ��˺�

	bool is_valid = true;						// �ӵ��Ƿ���Ч����������˺���
	bool can_remove = false;					// �ӵ��Ƿ����ɾ��

	PlayerID target_player_id = PlayerID::P1;					// �ӵ�Ŀ�꣨���ˣ�

	std::function < void() > touch_callback;	// �ӵ���ײ�󴥷��Ļص�����

};

