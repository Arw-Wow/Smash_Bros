#pragma once

#include <graphics.h>
#include <functional>	//回调函数

#include "Tools.h"
#include "Atlas.h"
#include "Camera.h"

class Animation
{
public:

	Animation() = default;

	~Animation() = default;
	
	// 动画重头播放
	void reset();

	void setAtlas(Atlas* new_altas);

	void setLoop(bool in);

	void setInterval(int ms);

	int getCurrentFrameIndex() const;

	IMAGE* getCurrentFrame() const;

	//是否播放完
	bool checkFinished();

	void onUpdate(int delta);

	void onDraw(const Camera& camera, int x, int y) const;

	void set_Callback(std::function< void() > callback);

private:

	int timer = 0;					//计时器
	int current_frame_index = 0;	//帧索引
	int interval = 0;				//帧间隔
	bool is_loop = true;			//是否循环播放

	Atlas* m_atlas = nullptr;

	std::function < void() > callback = nullptr;

};

/*
function是一个模板类，void()表示这个函数对象存储的函数类型是void且无参数。
这就是回调函数的原理：用function临时存储这个函数，之后可以在某个时刻调用callback来调用之前存储的函数。（类似于函数指针）
*/
