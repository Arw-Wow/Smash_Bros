#pragma once

#include "Tools.h"

extern bool is_debug;

class Platform
{
public:

	struct TouchShape
	{
		double y;
		double left, right;
	};

public:
	
	Platform() = default;
	~Platform() = default;

	void setTouchPosition(int y, int left, int right)
	{
		m_touchshape.y = y;
		m_touchshape.left = left;
		m_touchshape.right = right;
	}

	void setRenderPosition(int x, int y)
	{
		render_position.x = x;
		render_position.y = y;
	}

	double getLeft() const
	{
		return m_touchshape.left;
	}

	double getRight() const
	{
		return m_touchshape.right;
	}

	double getY() const
	{
		return m_touchshape.y;
	}

	void setImage(IMAGE* img)
	{
		this->img = img;
	}

	void onDraw(const Camera& camera)
	{
		putimage_alpha(camera, render_position.x, render_position.y, img);

		if (is_debug)
		{
			setlinecolor(YELLOW);
			line_alpha(camera, (int)m_touchshape.left, (int)m_touchshape.y, (int)m_touchshape.right, (int)m_touchshape.y);
		}
	}

private:

	TouchShape m_touchshape;				// 碰撞位置
	IMAGE* img = nullptr;					// 自己的图片
	POINT render_position = { 0 };			// 渲染位置（数据和渲染分离）

};

