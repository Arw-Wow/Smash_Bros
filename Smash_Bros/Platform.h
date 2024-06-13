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

	void setTouchPosition(int y, int left, int right);

	void setRenderPosition(int x, int y);

	double getLeft() const;

	double getRight() const;

	double getY() const;

	void setImage(IMAGE* img);

	void onDraw(const Camera& camera);

private:

	TouchShape m_touchshape;				// 碰撞位置
	IMAGE* img = nullptr;					// 自己的图片
	POINT render_position = { 0 };			// 渲染位置（数据和渲染分离）

};

