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

	int pass_time = 0;	//�ѹ�ʱ��
	int wait_time = 0;	//�ȴ�ʱ��
	bool paused = false;	//�Ƿ���ͣ
	bool shotted = false;	//�Ƿ񱻴�����
	bool one_shot = false;	//�Ƿ�Ϊ���δ���
	
	std::function < void() > shot_callback;	// �ص���������ʱ������ʱ����callback

};

