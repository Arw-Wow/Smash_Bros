#pragma once

#include <graphics.h>

#include "Tools.h"

class StatusBar
{
public:
	StatusBar() = default;

	~StatusBar() = default;

	void set_hp(int val);

	void set_mp(int val);

	void set_position(int x, int y);

	void set_avatar(IMAGE* img);
	
	void on_draw();



private:

	int hp = 0;
	int mp = 0;
	IMAGE* img_avatar = nullptr;	// Í·ÏñÍ¼Æ¬
	POINT position = { 0 };			// äÖÈ¾Î»ÖÃ
	int bar_width = 275;			// ×´Ì¬Ìõ¿í¶È
};

