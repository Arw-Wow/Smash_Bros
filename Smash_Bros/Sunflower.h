#pragma once
#include "Player.h"

#include "SunBullet.h"
#include "SunBullet_ex.h"

extern Atlas atlas_sunflower_idle_left;				    	// ���տ�����������ö���ͼ��
extern Atlas atlas_sunflower_idle_right;					// ���տ������ҵ����ö���ͼ��
extern Atlas atlas_sunflower_run_left;						// ���տ�������ı��ܶ���ͼ��
extern Atlas atlas_sunflower_run_right;			    		// ���տ������ҵı��ܶ���ͼ��
extern Atlas atlas_sunflower_attack_ex_left;				// ���տ�����������⹥������ͼ��
extern Atlas atlas_sunflower_attack_ex_right;				// ���տ������ҵ����⹥������ͼ��
extern Atlas atlas_sunflower_die_left;						// ���տ����������������ͼ��
extern Atlas atlas_sunflower_die_right;						// ���տ������ҵ���������ͼ��

extern Atlas atlas_sun_text;								// ���ա��ı�ͼ��

extern Player* player_1;
extern Player* player_2;

class Sunflower :
    public Player
{
public:

    Sunflower();

    ~Sunflower() = default;

	void onAttack() override;

	void onAttack_ex() override;

	void onUpdate(int delta) override;

	void onDraw(const Camera& camera) override;

private:

	const double speed_sun_ex = 0.15;				// ���⹥�����������ٶ�
	const Vector2 velocity_sun = { 0.4, -0.7 };	// ��ͨ����������ٶȣ�Ĭ������

	Animation animation_sun_text;
	bool is_sun_text_visible;	//�Ƿ���ʾ

};

