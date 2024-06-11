#pragma once

#include "Scene.h"

extern Scene* menu_scene;	//���߱�������ȫ��Ѱ��menu_scene�������ȡ��menu_scene������
extern Scene* selector_scene;
extern Scene* game_scene;

class SceneManager
{
public:

	enum SceneType
	{
		Menu, Selector, Game, 
	};


public:
	
	SceneManager() = default;
	~SceneManager() = default;

	// ���õ�ǰ������������onEnter����һ����main�е��ã���ֻ�ڵ�һ�ε��ã�
	void setCurrentScene(Scene* scene)
	{
		current_scene = scene;
		current_scene->onEnter();
	}

	// ��ת���� 
	// ����switch����һ���ڸ������������е��ã�Ϊ�˱��������໥���ã����������ΪSceneTypeö����
	// дmanager��Ҳ��Ϊ�˼��з�װ�������໥�����Լ�����ͬ�����
	void switchTo(SceneType type)
	{
		current_scene->onExit();
		switch (type)
		{
		case SceneManager::Menu:
			current_scene = menu_scene;
			break;
		case SceneManager::Selector:
			current_scene = selector_scene;
			break;
		case SceneManager::Game:
			current_scene = game_scene;
			break;
		}
		current_scene->onEnter();
	}

	void onUpdate(int delta)
	{
		current_scene->onUpdate(delta);
	}

	void onDraw(const Camera& camera)
	{
		current_scene->onDraw(camera);
	}

	void onInput(const ExMessage& msg)
	{
		current_scene->onInput(msg);
	}


private:

	Scene* current_scene = nullptr;


};

