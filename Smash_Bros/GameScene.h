#pragma once

#include <vector>

#include "Tools.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Platform.h"
#include "Player.h"
#include "PlayerType.h"
#include "StatusBar.h"

extern IMAGE img_sky;										// ���ͼƬ
extern IMAGE img_hills;										// ɽͼƬ
extern IMAGE img_platform_large;							// ��ƽ̨ͼƬ
extern IMAGE img_platform_small;							// Сƽ̨ͼƬ

extern IMAGE img_avatar_peashooter;							//�㶹����ͷ��ͼƬ
extern IMAGE img_avatar_sunflower;							//���տ�ͷ��ͼƬ
extern IMAGE img_avatar_gloomshroom;
extern IMAGE img_avatar_nut;

extern IMAGE img_1P_cursor;									// 1Pָʾ���ͼƬ
extern IMAGE img_2P_cursor;									// 2Pָʾ���ͼƬ

extern IMAGE img_1P_winner;									//1P��ʤ�ı�ͼƬ
extern IMAGE img_2P_winner;									//2P��ʤ�ı�ͼƬ
extern IMAGE img_winner_bar;								//��һ�ʤ����ͼƬ

extern SceneManager* scene_manager;

extern Camera main_camera;

extern std::vector <Platform> platform_list;

extern Player* player_1;
extern Player* player_2;

extern bool is_debug;


class GameScene :
    public Scene
{
public:

    GameScene() = default;

    ~GameScene() = default;

	//���볡��
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

	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	POINT pos_render_large_platform = { 0 };
	POINT pos_render_small_platform_1 = { 0 };
	POINT pos_render_small_platform_2 = { 0 };
	POINT pos_render_small_platform_3 = { 0 };

	StatusBar status_bar_p1;
	StatusBar status_bar_p2;

	bool is_game_over = false;	// ��Ϸ�Ƿ����

	Timer timer_cursor_display;
	bool is_cursor_display = true;	// �Ƿ���ʾ���

	Timer timer_win_img_stay;	// ��Ϸ���������ʤ��ͼƬ��ֹ��ʾ�ļ�ʱ��
	bool is_win_img_slide = false;
	POINT pos_img_1P_winner = { 0 };
	POINT pos_img_2P_winner = { 0 };
	POINT pos_img_winner_bar = { 0 };
	double win_img_slide_speed = 0.8;

	PlayerID id_winner = PlayerID::P1;

};

