#pragma once

#include <functional>

class Timer
{
public:

	Timer() = default;

	~Timer() = default;

	void restart();

	void setWaitTime(int val);

	void setOneShot(bool in);

	void setShotCallback(std::function < void() > callback);

	void pause();

	void resume();

	void onUpdate(int delta);



private:

	int pass_time = 0;	//已过时间
	int wait_time = 0;	//等待时间
	bool paused = false;	//是否暂停
	bool shotted = false;	//是否被触发过
	bool one_shot = false;	//是否为单次触发
	
	std::function < void() > shot_callback;	// 回调函数，计时器触发时调用callback

};

