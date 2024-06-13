#pragma once
#include "Player.h"
#include "PeaBullet.h"

extern Atlas atlas_peashooter_idle_left;					// �㶹���ֳ���������ö���ͼ��
extern Atlas atlas_peashooter_idle_right;					// �㶹���ֳ����ҵ����ö���ͼ��
extern Atlas atlas_peashooter_run_left;		    			// �㶹���ֳ�����ı��ܶ���ͼ��
extern Atlas atlas_peashooter_run_right;					// �㶹���ֳ����ҵı��ܶ���ͼ��
extern Atlas atlas_peashooter_attack_ex_left;				// �㶹���ֳ���������⹥������ͼ��
extern Atlas atlas_peashooter_attack_ex_right;				// �㶹���ֳ����ҵ����⹥������ͼ��
extern Atlas atlas_peashooter_die_left;						// �㶹���ֳ��������������ͼ��
extern Atlas atlas_peashooter_die_right;					// �㶹���ֳ����ҵ���������ͼ��

extern std::vector <Bullet*> bullet_list;

class Peashooter :
    public Player
{
public:

    Peashooter();

    ~Peashooter() = default;

    void onAttack() override;

    void onAttack_ex() override;

	void onUpdate(int delta) override;

private:

    void spawn_pea_bullet(double speed);

private:

    const double speed_pea = 0.75;          // �ӵ������ƶ��ٶȲ�Ӧ�����ӵ���������ԣ���Ӧ���Ƿ����ӵ��ġ�ǹ�������ԣ����Է�װ��player�С����ӵ��ി�⻯
    const double speed_pea_ex = 1.5;

	const int attack_ex_duration = 2500;	//���⹥������ʱ��

	Timer timer_attack_ex;	//���⹥��״̬��ʱ��
	Timer timer_spawn_pea_ex;	//���⹥���ӵ����ɼ�ʱ��


};

