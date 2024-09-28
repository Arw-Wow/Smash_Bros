#pragma once

#include <vector>

#include "Tools.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Platform.h"
#include "Player.h"
#include "PlayerType.h"
#include "StatusBar.h"

extern IMAGE img_sky;										// 天空图片
extern IMAGE img_hills;										// 山图片
extern IMAGE img_platform_large;							// 大平台图片
extern IMAGE img_platform_small;							// 小平台图片

extern IMAGE img_avatar_peashooter;							//豌豆射手头像图片
extern IMAGE img_avatar_sunflower;							//向日葵头像图片
extern IMAGE img_avatar_gloomshroom;
extern IMAGE img_avatar_nut;

extern IMAGE img_1P_cursor;									// 1P指示光标图片
extern IMAGE img_2P_cursor;									// 2P指示光标图片

extern IMAGE img_1P_winner;									//1P获胜文本图片
extern IMAGE img_2P_winner;									//2P获胜文本图片
extern IMAGE img_winner_bar;								//玩家获胜背景图片

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

	//进入场景
	void onEnter();
	
	//处理数据
	void onUpdate(int delta);
	
	//渲染绘图
	void onDraw(const Camera& camera);
	
	//处理输入
	void onInput(const ExMessage& msg);
	
	//退出场景
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

	bool is_game_over = false;	// 游戏是否结束

	Timer timer_cursor_display;
	bool is_cursor_display = true;	// 是否显示光标

	Timer timer_win_img_stay;	// 游戏结束后玩家胜利图片静止显示的计时器
	bool is_win_img_slide = false;
	POINT pos_img_1P_winner = { 0 };
	POINT pos_img_2P_winner = { 0 };
	POINT pos_img_winner_bar = { 0 };
	double win_img_slide_speed = 0.8;

	PlayerID id_winner = PlayerID::P1;

};

