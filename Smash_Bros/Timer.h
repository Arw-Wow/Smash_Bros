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
		// ����Ҫдstart����������timer����Ϊtimerֻ����updateʱ�Ż��ۼ�ʱ�䣬��һ�ε���update����start��

		//�����ͣ�Ͳ�����
		if (paused)
			return;

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			// ���callbackδ�����ã��Ͳ����������callback�������ˣ�������ǵ��δ�������ֱ�ӵ�ʱ����������ǵ��δ��������ǻ�δ����������Ҳֱ�ӵ�ʱ������
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

	int pass_time = 0;	//�ѹ�ʱ��
	int wait_time = 0;	//�ȴ�ʱ��
	bool paused = false;	//�Ƿ���ͣ
	bool shotted = false;	//�Ƿ񱻴�����
	bool one_shot = false;	//�Ƿ�Ϊ���δ���
	
	std::function < void() > shot_callback;	// �ص���������ʱ������ʱ����callback

};

