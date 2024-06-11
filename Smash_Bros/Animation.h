#pragma once

#include <graphics.h>
#include <functional>	//�ص�����

#include "Tools.h"
#include "Atlas.h"
#include "Camera.h"

class Animation
{
public:

	Animation() = default;
	~Animation() = default;
	
	// ������ͷ����
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

	//�Ƿ񲥷���
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

	int timer = 0;					//��ʱ��
	int current_frame_index = 0;	//֡����
	int interval = 0;				//֡���
	bool is_loop = true;			//�Ƿ�ѭ������

	Atlas* m_atlas = nullptr;

	std::function < void() > callback = nullptr;
};

/*
function��һ��ģ���࣬void()��ʾ�����������洢�ĺ���������void���޲�����
����ǻص�������ԭ����function��ʱ�洢���������֮�������ĳ��ʱ�̵���callback������֮ǰ�洢�ĺ������������ں���ָ�룩
*/
