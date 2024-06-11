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
	void onEnter()
	{
		mciSendString("play bgm_game repeat from 0", NULL, 0, NULL);

		player_1->setPosition(100, 100);
		player_2->setPosition(500, 100);
		player_1->setFacingleft(false);
		player_2->setFacingleft(true);

		//居中显示（图片比窗口略大）
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_render_large_platform.x = 122;
		pos_render_large_platform.y = 455;

		pos_render_small_platform_1.x = 175;
		pos_render_small_platform_1.y = 360;

		pos_render_small_platform_2.x = 855;
		pos_render_small_platform_2.y = 360;

		pos_render_small_platform_3.x = 515;
		pos_render_small_platform_3.y = 225;

		platform_list.clear();
		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.setImage(&img_platform_large);
		large_platform.setRenderPosition(pos_render_large_platform.x, pos_render_large_platform.y);
		large_platform.setTouchPosition(pos_render_large_platform.y + 60, 
			pos_render_large_platform.x + 30, pos_render_large_platform.x + img_platform_large.getwidth() - 30);
		
		Platform& small_platform_1 = platform_list[1];
		small_platform_1.setImage(&img_platform_small);
		small_platform_1.setRenderPosition(pos_render_small_platform_1.x, pos_render_small_platform_1.y);
		small_platform_1.setTouchPosition(pos_render_small_platform_1.y + img_platform_small.getheight() / 2,
			pos_render_small_platform_1.x + 40, pos_render_small_platform_1.x + img_platform_small.getwidth() - 40);

		Platform& small_platform_2 = platform_list[2];
		small_platform_2.setImage(&img_platform_small);
		small_platform_2.setRenderPosition(pos_render_small_platform_2.x, pos_render_small_platform_2.y);
		small_platform_2.setTouchPosition(pos_render_small_platform_2.y + img_platform_small.getheight() / 2,
			pos_render_small_platform_2.x + 40, pos_render_small_platform_2.x + img_platform_small.getwidth() - 40);
		
		Platform& small_platform_3 = platform_list[3];
		small_platform_3.setImage(&img_platform_small);
		small_platform_3.setRenderPosition(pos_render_small_platform_3.x, pos_render_small_platform_3.y);
		small_platform_3.setTouchPosition(pos_render_small_platform_3.y + img_platform_small.getheight() / 2,
			pos_render_small_platform_3.x + 40, pos_render_small_platform_3.x + img_platform_small.getwidth() - 40);

		// 设置p1头像
		switch (player_1->getType())
		{
		case PlayerType::PeaShooter:
			status_bar_p1.set_avatar(&img_avatar_peashooter);
			break;
		case PlayerType::SunFlower:
			status_bar_p1.set_avatar(&img_avatar_sunflower);
			break;
		}

		// 设置p2头像
		switch (player_2->getType())
		{
		case PlayerType::PeaShooter:
			status_bar_p2.set_avatar(&img_avatar_peashooter);
			break;
		case PlayerType::SunFlower:
			status_bar_p2.set_avatar(&img_avatar_sunflower);
			break;
		}

		status_bar_p1.set_position(235, 625);
		status_bar_p2.set_position(675, 625);
	}
	
	//处理数据
	void onUpdate(int delta)
	{
		player_1->onUpdate(delta);
		player_2->onUpdate(delta);

		main_camera.onUpdate(delta);

		// 删除可删除的子弹（不用erase，因为是new出来的必须要delete（是指针）否则内存泄露）
		for (int i = 0; i < bullet_list.size(); i++)
		{
			if (bullet_list[i]->checkCanRemove())
			{
				delete bullet_list[i];
				std::swap(bullet_list[i], bullet_list.back());
				bullet_list.pop_back();
			}
		}

		for (Bullet* bullet : bullet_list)
		{
			bullet->onUpdate(delta);
		}

		status_bar_p1.set_hp(player_1->get_hp());
		status_bar_p1.set_mp(player_1->get_mp());
		status_bar_p2.set_hp(player_2->get_hp());
		status_bar_p2.set_mp(player_2->get_mp());
	}
	
	//渲染绘图
	void onDraw(const Camera& camera)
	{
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);
		putimage_alpha(camera, pos_render_large_platform.x, pos_render_large_platform.y, &img_platform_large);

		for (Platform& platform : platform_list)
		{
			platform.onDraw(camera);
		}

		if (is_debug)
		{
			settextcolor(RED);
			outtextxy(15, 15, "调试模式已开启，按'Q'键关闭");
		}

		player_1->onDraw(camera);
		player_2->onDraw(camera);

		for (Bullet* bullet : bullet_list)
		{
			bullet->onDraw(camera);
		}

		status_bar_p1.on_draw();
		status_bar_p2.on_draw();
	}
	
	//处理输入
	void onInput(const ExMessage& msg)
	{	
		player_1->onInput(msg);
		player_2->onInput(msg);

		switch (msg.message)
		{
		case WM_KEYUP:
			switch (msg.vkcode)
			{
				case 0x51:	//'Q' 开启or关闭调试模式
					is_debug = !is_debug;
				break;
			}
			break;

		default:
			break;
		}

	}
	
	//退出场景
	void onExit()
	{
		mciSendString("close bgm_game", NULL, 0, NULL);
	}



private:

	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	POINT pos_render_large_platform = { 0 };
	POINT pos_render_small_platform_1 = { 0 };
	POINT pos_render_small_platform_2 = { 0 };
	POINT pos_render_small_platform_3 = { 0 };

	StatusBar status_bar_p1;
	StatusBar status_bar_p2;

};

