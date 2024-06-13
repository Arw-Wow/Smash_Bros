#pragma once

#include <graphics.h>

#include "Camera.h"

class Scene
{
public:

	Scene() = default;

	~Scene() = default;

	//���볡��
	virtual void onEnter();
	
	//��������
	virtual void onUpdate(int delta);
	
	//��Ⱦ��ͼ
	virtual void onDraw(const Camera& camera);
	
	//��������
	virtual void onInput(const ExMessage& msg);
	
	//�˳�����
	virtual void onExit();

private:



};

