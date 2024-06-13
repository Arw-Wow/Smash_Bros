#pragma once

#include <iostream>

#include "Atlas.h"
#include "SceneManager.h"
#include "Scene.h"

extern IMAGE img_menu_background;							//���˵�����ͼƬ

extern SceneManager* scene_manager;


class MenuScene : public Scene
{
public:

	MenuScene() = default;
	~MenuScene() = default;

	//���볡��
	void onEnter()
	{
		mciSendString("play bgm_menu repeat from 0", NULL, 0, NULL);
	}
	
	//��������
	void onUpdate(int delta)
	{
	}
	
	//��Ⱦ��ͼ
	void onDraw(const Camera& camera)
	{
		putimage(0, 0, &img_menu_background);

	}
	
	//��������
	void onInput(const ExMessage& msg)
	{
		if (msg.message == WM_KEYUP)
		{
			mciSendString("play ui_confirm from 0", NULL, 0, NULL);
			scene_manager->switchTo(SceneManager::SceneType::Selector);
		}
	}
	
	//�˳�����
	void onExit()
	{
		mciSendString("stop bgm_menu", NULL, 0, NULL);
	}


private:


};

