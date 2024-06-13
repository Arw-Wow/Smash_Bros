#include "Timer.h"

void Timer::restart()
{
    pass_time = 0;
    shotted = false;
}

void Timer::setWaitTime(int val)
{
    wait_time = val;
}

void Timer::setOneShot(bool in)
{
    one_shot = in;
}

void Timer::setShotCallback(std::function<void()> callback)
{
    this->shot_callback = callback;
}

void Timer::pause()
{
    paused = true;
}

void Timer::resume()
{
    paused = false;
}

void Timer::onUpdate(int delta)
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
