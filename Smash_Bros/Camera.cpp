#include "Camera.h"

Camera::Camera()
{
    //д�ڹ��캯������Ϊ�˴�����ͬʱ���ú�һЩ������������Ҫ���û���������
    timer_shake.setOneShot(true);
    timer_shake.setShotCallback(
        [&]() {
            //��ʱֹͣ���������������λ��
            is_shaking = false;
            this->reset();
        }
    );
}

const Vector2& Camera::getPosition() const
{
    return position;
}

//����cameraλ�õ���0��0��������Щ��Ϸ�����õ������Ϊ���ĵ�λ�ã����Ƚ����ָ����Ϊȫ�ֱ�������extern���ָ�룬������ʹ�ã�

void Camera::reset()
{
    position.x = 0;
    position.y = 0;
}

void Camera::onUpdate(int delta)
{
    // �ƶ�����ͷ
    // const Vector2 speed(-0.35, 0);	//�ٶ�ʸ������������
    // position += speed * (double)delta;	//����������position�ƶ���ʱ���й�,��������ִ�д����й�

    timer_shake.onUpdate(delta);

    if (is_shaking)
    {	// -1 ~ 1 �����С�� ���� ҡ��ǿ��
        position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
        position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
    }
}

void Camera::shake(double strength, int shake_time)
{
    is_shaking = true;
    shaking_strength = strength;
    timer_shake.setWaitTime(shake_time);
    timer_shake.restart();
}
