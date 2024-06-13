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


};

