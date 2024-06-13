#include "Platform.h"

void Platform::setTouchPosition(int y, int left, int right)
{
    m_touchshape.y = y;
    m_touchshape.left = left;
    m_touchshape.right = right;
}

void Platform::setRenderPosition(int x, int y)
{
    render_position.x = x;
    render_position.y = y;
}

double Platform::getLeft() const
{
    return m_touchshape.left;
}

double Platform::getRight() const
{
    return m_touchshape.right;
}

double Platform::getY() const
{
    return m_touchshape.y;
}

void Platform::setImage(IMAGE* img)
{
    this->img = img;
}

void Platform::onDraw(const Camera& camera)
{
    putimage_alpha(camera, render_position.x, render_position.y, img);

    if (is_debug)
    {
        setlinecolor(YELLOW);
        line_alpha(camera, (int)m_touchshape.left, (int)m_touchshape.y, (int)m_touchshape.right, (int)m_touchshape.y);
    }
}
