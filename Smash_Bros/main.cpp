#include <iostream>
#include <graphics.h>

#include <vector>

#include "Atlas.h"
#include "Tools.h"
#include "Animation.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include "SelectorScene.h"
#include "GameScene.h"
#include "Camera.h"
#include "Platform.h"
#include "Player.h"
#include "Bullet.h"

#pragma comment(lib, "Winmm.lib")

/*������������������������������������������������Դ����������������������������������������������������������*/

IMAGE img_menu_background;							//���˵�����ͼƬ

IMAGE img_VS;										// VS��ͼƬ
IMAGE img_1P;										// 1P�ı�ͼƬ
IMAGE img_2P;										// 2P�ı�ͼƬ
IMAGE img_1P_desc;									// 1P��λ����ͼƬ
IMAGE img_2P_desc;									// 2P��λ����ͼƬ
IMAGE img_gravestone_left;							// �����Ĺ��ͼƬ
IMAGE img_gravestone_right;							// ���ҵ�Ĺ��ͼƬ
IMAGE img_selector_tip;								// ѡ���ɫ������ʾͼƬ
IMAGE img_selector_background;						// ѡ���ɫ���汳��ͼƬ
IMAGE img_1P_selector_btn_idle_left;				// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_idle_right;				// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_down_left;				// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_down_right;				// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_idle_left;				// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_idle_right;				// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_down_left;				// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_down_right;				// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_peashooter_selector_background_left;		// ѡ���ɫ�����㶹���ֳ�����ı���ͼƬ
IMAGE img_peashooter_selector_background_right;		// ѡ���ɫ�����㶹���ֳ����ҵı���ͼƬ
IMAGE img_sunflower_selector_background_left;		// ѡ���ɫ�������տ�������ı���ͼƬ
IMAGE img_sunflower_selector_background_right;		// ѡ���ɫ�������տ������ҵı���ͼƬ

IMAGE img_sky;										// ���ͼƬ
IMAGE img_hills;									// ɽͼƬ
IMAGE img_platform_large;							// ��ƽ̨ͼƬ
IMAGE img_platform_small;							// Сƽ̨ͼƬ

IMAGE img_1P_cursor;								// 1Pָʾ���ͼƬ
IMAGE img_2P_cursor;								// 2Pָʾ���ͼƬ

Atlas atlas_peashooter_idle_left;					// �㶹���ֳ���������ö���ͼ��
Atlas atlas_peashooter_idle_right;					// �㶹���ֳ����ҵ����ö���ͼ��
Atlas atlas_peashooter_run_left;					// �㶹���ֳ�����ı��ܶ���ͼ��
Atlas atlas_peashooter_run_right;					// �㶹���ֳ����ҵı��ܶ���ͼ��
Atlas atlas_peashooter_attack_ex_left;				// �㶹���ֳ���������⹥������ͼ��
Atlas atlas_peashooter_attack_ex_right;				// �㶹���ֳ����ҵ����⹥������ͼ��
Atlas atlas_peashooter_die_left;					// �㶹���ֳ��������������ͼ��
Atlas atlas_peashooter_die_right;					// �㶹���ֳ����ҵ���������ͼ��

Atlas atlas_sunflower_idle_left;					// ���տ�����������ö���ͼ��
Atlas atlas_sunflower_idle_right;					// ���տ������ҵ����ö���ͼ��
Atlas atlas_sunflower_run_left;						// ���տ�������ı��ܶ���ͼ��
Atlas atlas_sunflower_run_right;					// ���տ������ҵı��ܶ���ͼ��
Atlas atlas_sunflower_attack_ex_left;				// ���տ�����������⹥������ͼ��
Atlas atlas_sunflower_attack_ex_right;				// ���տ������ҵ����⹥������ͼ��
Atlas atlas_sunflower_die_left;						// ���տ����������������ͼ��
Atlas atlas_sunflower_die_right;					// ���տ������ҵ���������ͼ��

IMAGE img_pea;										// �㶹ͼƬ
Atlas atlas_pea_break;								// �㶹����ͼ��
Atlas atlas_sun;									// ̫��ͼ��
Atlas atlas_sun_explode;							//̫����ըͼ��
Atlas atlas_sun_ex;									//����̫��ͼ��
Atlas atlas_sun_ex_explode;							//����̫����ըͼ��
Atlas atlas_sun_text;								// ���ա��ı�ͼ��

Atlas atlas_run_effect;								//����Ч��ͼ��
Atlas atlas_jump_effect;							//��ԾЧ��ͼ��
Atlas atlas_land_effect;							//���Ч��ͼ��

IMAGE img_1P_winner;								//1P��ʤ�ı�ͼƬ
IMAGE img_2P_winner;								//2P��ʤ�ı�ͼƬ
IMAGE img_winner_bar;								//��һ�ʤ����ͼƬ

IMAGE img_avatar_peashooter;						//�㶹����ͷ��ͼƬ
IMAGE img_avatar_sunflower;							//���տ�ͷ��ͼƬ

/*������������������������������������������������������������������������������������������������������������*/



/*����������������������������������������������������Դ���ء�������������������������������������������������*/
void loadGameResources()
{
	AddFontResourceEx("res/IPix.ttf", FR_PRIVATE, NULL);	//ò�Ƽ��ز��ɹ��������Ǳ�������

	loadimage(&img_menu_background, "res/menu_background.png");

	loadimage(&img_VS, "res/VS.png");
	loadimage(&img_1P, "res/1P.png");
	loadimage(&img_2P, "res/2P.png");
	loadimage(&img_1P_desc, "res/1P_desc.png");
	loadimage(&img_2P_desc, "res/2P_desc.png");
	loadimage(&img_gravestone_right, "res/gravestone.png");
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, "res/selector_tip.png");
	loadimage(&img_selector_background, "res/selector_background.png");

	loadimage(&img_1P_selector_btn_idle_right, "res/1P_selector_btn_idle.png");
	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, "res/1P_selector_btn_down.png");
	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);

	loadimage(&img_2P_selector_btn_idle_right, "res/2P_selector_btn_idle.png");
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, "res/2P_selector_btn_down.png");
	flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);

	loadimage(&img_peashooter_selector_background_right, "res/peashooter_selector_background.png");
	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, "res/sunflower_selector_background.png");
	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, "res/sky.png");
	loadimage(&img_hills, "res/hills.png");
	loadimage(&img_platform_large, "res/platform_large.png");
	loadimage(&img_platform_small, "res/platform_small.png");

	loadimage(&img_1P_cursor, "res/1P_cursor.png");
	loadimage(&img_2P_cursor, "res/2P_cursor.png");

	atlas_peashooter_idle_right.loadFromFile("res/peashooter_idle_%d.png", 9);
	atlas_peashooter_idle_right.saveFlipAtlasTo(atlas_peashooter_idle_left);
	atlas_peashooter_run_right.loadFromFile("res/peashooter_run_%d.png", 5);
	atlas_peashooter_run_right.saveFlipAtlasTo(atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.loadFromFile("res/peashooter_attack_ex_%d.png", 3);
	atlas_peashooter_attack_ex_right.saveFlipAtlasTo(atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.loadFromFile("res/peashooter_die_%d.png", 4);
	atlas_peashooter_die_right.saveFlipAtlasTo(atlas_peashooter_die_left);

	atlas_sunflower_idle_right.loadFromFile("res/sunflower_idle_%d.png", 8);
	atlas_sunflower_idle_right.saveFlipAtlasTo(atlas_sunflower_idle_left);
	atlas_sunflower_run_right.loadFromFile("res/sunflower_run_%d.png", 5);
	atlas_sunflower_run_right.saveFlipAtlasTo(atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.loadFromFile("res/sunflower_attack_ex_%d.png", 9);
	atlas_sunflower_attack_ex_right.saveFlipAtlasTo(atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.loadFromFile("res/sunflower_die_%d.png", 2);
	atlas_sunflower_die_right.saveFlipAtlasTo(atlas_sunflower_die_left);

	loadimage(&img_pea, "res/pea.png");
	atlas_pea_break.loadFromFile("res/pea_break_%d.png", 3);
	atlas_sun.loadFromFile("res/sun_%d.png", 5);
	atlas_sun_explode.loadFromFile("res/sun_explode_%d.png", 5);
	atlas_sun_ex.loadFromFile("res/sun_ex_%d.png", 5);
	atlas_sun_ex_explode.loadFromFile("res/sun_ex_explode_%d.png", 5);
	atlas_sun_text.loadFromFile("res/sun_text_%d.png", 6);

	atlas_run_effect.loadFromFile("res/run_effect_%d.png", 4);
	atlas_jump_effect.loadFromFile("res/jump_effect_%d.png", 5);
	atlas_land_effect.loadFromFile("res/land_effect_%d.png", 2);

	loadimage(&img_1P_winner, "res/1P_winner.png");
	loadimage(&img_2P_winner, "res/2P_winner.png");
	loadimage(&img_winner_bar, "res/winner_bar.png");

	loadimage(&img_avatar_peashooter, "res/avatar_peashooter.png");
	loadimage(&img_avatar_sunflower, "res/avatar_sunflower.png");

	mciSendString("open res/bgm_menu.mp3 alias bgm_menu", NULL, 0, NULL);
	mciSendString("open res/bgm_selector.mp3 alias bgm_selector", NULL, 0, NULL);
	mciSendString("open res/bgm_game.mp3 alias bgm_game", NULL, 0, NULL);
	mciSendString("open res/pea_break_1.mp3 alias pea_break_1", NULL, 0, NULL);
	mciSendString("open res/pea_break_2.mp3 alias pea_break_2", NULL, 0, NULL);
	mciSendString("open res/pea_break_3.mp3 alias pea_break_3", NULL, 0, NULL);
	mciSendString("open res/pea_shoot_1.mp3 alias pea_shoot_1", NULL, 0, NULL);
	mciSendString("open res/pea_shoot_1.mp3 alias pea_shoot_2", NULL, 0, NULL);
	mciSendString("open res/pea_shoot_ex.mp3 alias pea_shoot_ex", NULL, 0, NULL);
	mciSendString("open res/sun_explode.mp3 alias sun_explode", NULL, 0, NULL);
	mciSendString("open res/sun_explode_ex.mp3 alias sun_explode_ex", NULL, 0, NULL);
	mciSendString("open res/sun_text.mp3 alias sun_text", NULL, 0, NULL);
	mciSendString("open res/ui_confirm.wav alias ui_confirm", NULL, 0, NULL);
	mciSendString("open res/ui_switch.wav alias ui_switch", NULL, 0, NULL);
	mciSendString("open res/ui_win.wav alias ui_win", NULL, 0, NULL);

}
/*������������������������������������������������������������������������������������������������������������*/


bool is_debug = false;	//����ģʽ


SceneManager* scene_manager = nullptr;

Scene* menu_scene = nullptr;
Scene* selector_scene = nullptr;
Scene* game_scene = nullptr;

Camera main_camera;

std::vector <Platform> platform_list;
std::vector <Bullet*> bullet_list;

Player* player_1 = nullptr;
Player* player_2 = nullptr;



constexpr int FPS = 60;






int main()
{
	ExMessage msg;

	loadGameResources();

	initgraph(1280, 720);

	//����ȫ��������ʽ
	settextstyle(28, 0, "����");
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	scene_manager = new SceneManager();

	menu_scene = new MenuScene();
	selector_scene = new SelectorScene();
	game_scene = new GameScene();

	scene_manager->setCurrentScene(menu_scene);

	while (true)
	{
		DWORD frame_start_time = GetTickCount();

		//���մ�������
		while (peekmessage(&msg))
		{
			scene_manager->onInput(msg);		// input
		}
		
		//�����ϴ�update�����update��deltaʱ��
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		scene_manager->onUpdate(current_tick_time - last_tick_time);		// update
		last_tick_time = current_tick_time;

		//��Ⱦ
		cleardevice();
		scene_manager->onDraw(main_camera);		// draw
		FlushBatchDraw();

		//��̬����֡��
		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
	}

	EndBatchDraw();


	
	//�ͷ���Դ
	delete scene_manager;
	delete menu_scene;
	delete selector_scene;
	delete game_scene;
	for (int i = 0; i < bullet_list.size(); i++)
		delete bullet_list[i];
	delete player_1;
	delete player_2;



	return 0;
}

// 3758 ��