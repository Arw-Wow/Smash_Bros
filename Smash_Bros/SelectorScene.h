#pragma once

#include "SceneManager.h"
#include "Scene.h"
#include "Animation.h"
#include "Player.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "PlayerID.h"
#include "PlayerType.h"

extern IMAGE img_VS;										// VS��ͼƬ
extern IMAGE img_1P;										// 1P�ı�ͼƬ
extern IMAGE img_2P;										// 2P�ı�ͼƬ
extern IMAGE img_1P_desc;									// 1P��λ����ͼƬ
extern IMAGE img_2P_desc;									// 2P��λ����ͼƬ
extern IMAGE img_gravestone_left;							// �����Ĺ��ͼƬ
extern IMAGE img_gravestone_right;							// ���ҵ�Ĺ��ͼƬ
extern IMAGE img_selector_tip;								// ѡ���ɫ������ʾͼƬ
extern IMAGE img_selector_background;						// ѡ���ɫ���汳��ͼƬ
extern IMAGE img_1P_selector_btn_idle_left;					// 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_idle_right;				// 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_left;					// 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_right;				// 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_left;					// 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_right;				// 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_left;					// 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_right;				// 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_peashooter_selector_background_left;		// ѡ���ɫ�����㶹���ֳ�����ı���ͼƬ
extern IMAGE img_peashooter_selector_background_right;		// ѡ���ɫ�����㶹���ֳ����ҵı���ͼƬ
extern IMAGE img_sunflower_selector_background_left;		// ѡ���ɫ�������տ�������ı���ͼƬ
extern IMAGE img_sunflower_selector_background_right;		// ѡ���ɫ�������տ������ҵı���ͼƬ
	
extern Atlas atlas_peashooter_idle_left;					// �㶹���ֳ���������ö���ͼ��
extern Atlas atlas_sunflower_idle_left;						// ���տ�����������ö���ͼ��
extern Atlas atlas_peashooter_idle_right;					// �㶹���ֳ����ҵ����ö���ͼ��
extern Atlas atlas_sunflower_idle_right;					// ���տ������ҵ����ö���ͼ��

extern IMAGE img_avatar_peashooter;							//�㶹����ͷ��ͼƬ
extern IMAGE img_avatar_sunflower;							//���տ�ͷ��ͼƬ

extern Player* player_1;
extern Player* player_2;

extern SceneManager* scene_manager;

class SelectorScene :
    public Scene
{
public:

	SelectorScene() = default;

	~SelectorScene() = default;

	//���볡��������init�����������쵫Ҫ��ʼ����
	void onEnter();
	
	//��������
	void onUpdate(int delta);
	
	//��Ⱦ��ͼ
	void onDraw(const Camera& camera);
	
	//��������
	void onInput(const ExMessage& msg);
	
	//�˳�����
	void onExit();

private:

	POINT pos_img_VS = { 0 };							// VS ��ͼƬλ��
	POINT pos_img_tip = { 0 };							// ��ʾ��Ϣ�ı�ͼƬλ��
	POINT pos_img_1P = { 0 };							// 1P�ı�ͼƬλ��
	POINT pos_img_2P = { 0 };							// 2P�ı�ͼƬλ��
	POINT pos_img_1P_desc = { 0 };						// 1P��λ����ͼƬλ��
	POINT pos_img_2P_desc = { 0 };						// 2P��λ����ͼƬλ��
	POINT pos_img_1P_name = { 0 };						// 1P����λ��
	POINT pos_img_2P_name = { 0 };						// 2P����λ��
	POINT pos_img_1P_gravestone = { 0 };				// 1PĹ��λ��
	POINT pos_img_2P_gravestone = { 0 };				// 2PĹ��λ��
	POINT pos_animation_1P = { 0 };						// 1P����λ��
	POINT pos_animation_2P = { 0 };						// 2P����λ��
	POINT pos_1P_selector_btn_left = { 0 };				// 1P�����л���ťλ��
	POINT pos_1P_selector_btn_right = { 0 };			// 1P�����л���ťλ��
	POINT pos_2P_selector_btn_left = { 0 };				// 2P�����л���ťλ��
	POINT pos_2P_selector_btn_right = { 0 };			// 2P�����л���ťλ��

	Animation animation_1P_peashooter;						// 1P�㶹���ֶ���
	Animation animation_1P_sunflower;						// 1P���տ�����
	Animation animation_2P_peashooter;						// 2P�㶹���ֶ���
	Animation animation_2P_sunflower;						// 2P���տ�����

	PlayerType player_type_1 = PlayerType::PeaShooter;	// 1P��ɫ����
	PlayerType player_type_2 = PlayerType::SunFlower;	// 2P��ɫ����

	LPCTSTR str_peashooter_name = "�㶹����";				// �㶹���������ı�
	LPCTSTR str_sunflower_name = "���տ�";				// ���տ������ı�

	int selector_background_scorll_offset_x = 0;		// �������������

	bool is_btn_1P_left_down = false;					// 1P����Ƿ���
	bool is_btn_1P_right_down = false;					// 1P�Ҽ��Ƿ���
	bool is_btn_2P_left_down = false;					// 2P����Ƿ���
	bool is_btn_2P_right_down = false;					// 2P�Ҽ��Ƿ���

private:
	
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		//������Ӱ
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		
		//�����ı�
		settextcolor(WHITE);
		outtextxy(x, y, str);
	}

};

