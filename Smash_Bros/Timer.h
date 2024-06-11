#pragma once

#include <functional>

class Timer
{
public:

	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void setWaitTime(int val)
	{
		wait_time = val;
	}

	void setOneShot(bool in)
	{
		one_shot = in;
	}

	void setShotCallback(std::function < void() > callback)
	{
		this->shot_callback = callback;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	void onUpdate(int delta)
	{
		// 不需要写start函数来启动timer，因为timer只有在update时才会累加时间，第一次调用update就是start了

		//如果暂停就不更新
		if (paused)
			return;

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			// 如果callback未被设置，就不触发。如果callback被设置了：如果不是单次触发，就直接到时触发；如果是单次触发，但是还未被触发过，也直接到时触发。
			if ((!one_shot || (one_shot && !shotted)) && shot_callback)
				shot_callback();

			shotted = true;

			if (!one_shot)
				pass_time -= wait_time;
			else
				pass_time = 0;
		}
		

	}



private:

	int pass_time = 0;	//已过时间
	int wait_time = 0;	//等待时间
	bool paused = false;	//是否暂停
	bool shotted = false;	//是否被触发过
	bool one_shot = false;	//是否为单次触发
	
	std::function < void() > shot_callback;	// 回调函数，计时器触发时调用callback

};

