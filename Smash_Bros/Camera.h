#pragma once

#include "Timer.h"
#include "Vector2.h"

// 这种在各个类中都要使用的东西就要单独封装，且越独立越好，避免相互包含，便于调度管理
class Camera
{
public:

	Camera();

	~Camera() = default;
	
	const Vector2& getPosition() const;

	//重置camera位置到（0，0）处（有些游戏是重置到以玩家为中心的位置，就先将玩家指针设为全局变量，再extern玩家指针，在这里使用）
	void reset();

	void onUpdate(int delta);

	void shake(double strength, int shake_time);



private:

	Vector2 position;	// camera坐标是窗口坐标左上角

	Timer timer_shake;				//摄像机抖动计时器
	bool is_shaking = false;		//摄像机是否抖动
	double shaking_strength = 0;	//摄像机抖动幅度

};

