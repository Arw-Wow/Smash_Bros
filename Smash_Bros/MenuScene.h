#pragma once

#include <iostream>

#include "Atlas.h"
#include "SceneManager.h"
#include "Scene.h"

extern IMAGE img_menu_background;							//主菜单背景图片

extern SceneManager* scene_manager;


class MenuScene : public Scene
{
public:

	MenuScene() = default;
	~MenuScene() = default;

	//进入场景
	void onEnter()
	{
		mciSendString("play bgm_menu repeat from 0", NULL, 0, NULL);
	}
	
	//处理数据
	void onUpdate(int delta)
	{
	}
	
	//渲染绘图
	void onDraw(const Camera& camera)
	{
		putimage(0, 0, &img_menu_background);

	}
	
	//处理输入
	void onInput(const ExMessage& msg)
	{
		if (msg.message == WM_KEYUP)
		{
			mciSendString("play ui_confirm from 0", NULL, 0, NULL);
			scene_manager->switchTo(SceneManager::SceneType::Selector);
		}
	}
	
	//退出场景
	void onExit()
	{
		mciSendString("stop bgm_menu", NULL, 0, NULL);
	}


private:


};

