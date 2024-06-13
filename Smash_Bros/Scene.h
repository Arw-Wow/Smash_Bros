#pragma once

#include <graphics.h>

#include "Camera.h"

class Scene
{
public:

	Scene() = default;

	~Scene() = default;

	//进入场景
	virtual void onEnter();
	
	//处理数据
	virtual void onUpdate(int delta);
	
	//渲染绘图
	virtual void onDraw(const Camera& camera);
	
	//处理输入
	virtual void onInput(const ExMessage& msg);
	
	//退出场景
	virtual void onExit();

private:



};

