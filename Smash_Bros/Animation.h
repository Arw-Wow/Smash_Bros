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
	void reset();

	void setAtlas(Atlas* new_altas);

	void setLoop(bool in);

	void setInterval(int ms);

	int getCurrentFrameIndex() const;

	IMAGE* getCurrentFrame() const;

	//�Ƿ񲥷���
	bool checkFinished();

	void onUpdate(int delta);

	void onDraw(const Camera& camera, int x, int y) const;

	void set_Callback(std::function< void() > callback);

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
