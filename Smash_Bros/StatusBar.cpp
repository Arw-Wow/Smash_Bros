#include "StatusBar.h"

void StatusBar::set_hp(int val)
{
    hp = val;
}

void StatusBar::set_mp(int val)
{
    mp = val;
}

void StatusBar::set_position(int x, int y)
{
    position.x = x;
    position.y = y;
}

void StatusBar::set_avatar(IMAGE* img)
{
    img_avatar = img;
}

void StatusBar::on_draw()
{
    // 绘制头像
    putimage_alpha(position.x, position.y, img_avatar);

    // 绘制状态背景槽阴影
    int offset_shadow = 3;
    setfillcolor(RGB(5, 5, 5));
    solidroundrect(position.x + 100, position.y + 10, position.x + 100 + bar_width + 3 + offset_shadow, position.y + 33 + offset_shadow, 8, 8);	// hp, 后面两个是圆角矩形弧度
    solidroundrect(position.x + 100, position.y + 45, position.x + 100 + bar_width + 3 + offset_shadow, position.y + 68 + offset_shadow, 8, 8);	// mp, 再加一个3是槽的边缘宽度

    // 绘制状态背景槽本身
    setfillcolor(RGB(67, 47, 47));
    solidroundrect(position.x + 100, position.y + 10, position.x + 100 + bar_width + 3, position.y + 33, 8, 8);
    solidroundrect(position.x + 100, position.y + 45, position.x + 100 + bar_width + 3, position.y + 68, 8, 8);

    // 计算具体值条长度
    double hp_bar_width = bar_width * ((max(0, hp)) / 100.0);	//hp最多为100，这样实现了百分比。用max防止出现负数渲染。
    double mp_bar_width = bar_width * ((min(100, mp)) / 100.0);	// 用min是因为mp不会小于0但会大于100，这时防止溢出渲染。

    // 绘制状态具体值
    setfillcolor(RGB(197, 61, 67));		// 血条颜色
    solidroundrect(position.x + 100, position.y + 10, position.x + 100 + hp_bar_width + 3, position.y + 33, 8, 8);
    setfillcolor(RGB(83, 131, 195));	// 蓝条颜色
    solidroundrect(position.x + 100, position.y + 45, position.x + 100 + mp_bar_width + 3, position.y + 68, 8, 8);
}
