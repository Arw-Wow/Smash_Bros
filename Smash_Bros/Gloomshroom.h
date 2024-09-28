#pragma once

#include "Player.h"
#include "BubblesBullet_ex.h"

extern Atlas atlas_gloomshroom_idle_left;					// ���繽��������ö���ͼ��
extern Atlas atlas_gloomshroom_idle_right;					// ���繽�����ҵ����ö���ͼ��
extern Atlas atlas_gloomshroom_run_left;		    		// ���繽������ı��ܶ���ͼ��
extern Atlas atlas_gloomshroom_run_right;					// ���繽�����ҵı��ܶ���ͼ��
extern Atlas atlas_gloomshroom_attack_ex_left;				// ���繽����������⹥������ͼ��
extern Atlas atlas_gloomshroom_attack_ex_right;				// ���繽�����ҵ����⹥������ͼ��
extern Atlas atlas_gloomshroom_die_left;					// ���繽���������������ͼ��
extern Atlas atlas_gloomshroom_die_right;					// ���繽�����ҵ���������ͼ��

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


	Timer timer_attack_ex;	//���⹥��״̬��ʱ��
	Timer timer_bubbles_ex;	//���⹥��ʱ����

	const int attack_ex_duration = 2000;	//���⹥������ʱ��

};


