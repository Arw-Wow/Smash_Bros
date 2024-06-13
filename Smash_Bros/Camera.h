#pragma once

#include "Timer.h"
#include "Vector2.h"

// �����ڸ������ж�Ҫʹ�õĶ�����Ҫ������װ����Խ����Խ�ã������໥���������ڵ��ȹ���
class Camera
{
public:

	Camera();

	~Camera() = default;
	
	const Vector2& getPosition() const;

	//����cameraλ�õ���0��0��������Щ��Ϸ�����õ������Ϊ���ĵ�λ�ã����Ƚ����ָ����Ϊȫ�ֱ�������extern���ָ�룬������ʹ�ã�
	void reset();

	void onUpdate(int delta);

	void shake(double strength, int shake_time);



private:

	Vector2 position;	// camera�����Ǵ����������Ͻ�

	Timer timer_shake;				//�����������ʱ��
	bool is_shaking = false;		//������Ƿ񶶶�
	double shaking_strength = 0;	//�������������

};

