#include "Animation.h"

// 动画重头播放

void Animation::reset()
{
    timer = 0;
    current_frame_index = 0;
}

void Animation::setAtlas(Atlas* new_altas)
{
    reset();
    m_atlas = new_altas;
}

void Animation::setLoop(bool in)
{
    is_loop = in;
}

void Animation::setInterval(int ms)
{
    interval = ms;
}

int Animation::getCurrentFrameIndex() const
{
    return current_frame_index;
}

IMAGE* Animation::getCurrentFrame() const
{
    return m_atlas->getImage(current_frame_index);
}

//是否播放完

bool Animation::checkFinished()
{
    if (is_loop)
        return false;

    return (current_frame_index == m_atlas->getSize() - 1);
}

void Animation::onUpdate(int delta)
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

void Animation::onDraw(const Camera& camera, int x, int y) const
{
    putimage_alpha(camera, x, y, m_atlas->getImage(current_frame_index));
}

void Animation::set_Callback(std::function<void()> callback)
{
    this->callback = callback;
}
