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
	void reset()
	{
		timer = 0;
		current_frame_index = 0;
	}

	void setAtlas(Atlas* new_altas)
	{
		reset();
		m_atlas = new_altas;
	}

	void setLoop(bool in)
	{
		is_loop = in;
	}

	void setInterval(int ms)
	{
		interval = ms;
	}

	int getCurrentFrameIndex() const
	{
		return current_frame_index;
	}

	IMAGE* getCurrentFrame() const
	{
		return m_atlas->getImage(current_frame_index);
	}

	//是否播放完
	bool checkFinished()
	{
		if (is_loop)
			return false;

		return (current_frame_index == m_atlas->getSize() - 1);
	}

	void onUpdate(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer -= interval;
			current_frame_index++;
			if (current_frame_index >= m_atlas->getSize())
			{
				if (is_loop)
					current_frame_index = 0;
				else if (!is_loop)
				{
					current_frame_index = m_atlas->getSize() - 1;
					if (callback)
					{
						callback();
					}
				}
			}
		}
	}

	void onDraw(const Camera& camera, int x, int y) const
	{
		putimage_alpha(camera, x, y, m_atlas->getImage(current_frame_index));
	}

	void set_Callback(std::function< void() > callback)
	{
		this->callback = callback;
	}


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
