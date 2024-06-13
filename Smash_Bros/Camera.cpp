#include "Camera.h"

Camera::Camera()
{
    //写在构造函数中是为了创建的同时设置好一些东西，而不是要求用户自行设置
    timer_shake.setOneShot(true);
    timer_shake.setShotCallback(
        [&]() {
            //到时停止抖动并重置摄像机位置
            is_shaking = false;
            this->reset();
        }
    );
}

const Vector2& Camera::getPosition() const
{
    return position;
}

//重置camera位置到（0，0）处（有些游戏是重置到以玩家为中心的位置，就先将玩家指针设为全局变量，再extern玩家指针，在这里使用）

void Camera::reset()
{
    position.x = 0;
    position.y = 0;
}

void Camera::onUpdate(int delta)
{
    // 移动摄像头
    // const Vector2 speed(-0.35, 0);	//速度矢量，包含方向
    // position += speed * (double)delta;	//这样可以让position移动与时间有关,而不是与执行次数有关

    timer_shake.onUpdate(delta);

    if (is_shaking)
    {	// -1 ~ 1 的随机小数 乘以 摇晃强度
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
