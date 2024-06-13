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


};

