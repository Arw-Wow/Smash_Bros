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
    // ����ͷ��
    putimage_alpha(position.x, position.y, img_avatar);

    // ����״̬��������Ӱ
    int offset_shadow = 3;
    setfillcolor(RGB(5, 5, 5));
    solidroundrect(position.x + 100, position.y + 10, position.x + 100 + bar_width + 3 + offset_shadow, position.y + 33 + offset_shadow, 8, 8);	// hp, ����������Բ�Ǿ��λ���
    solidroundrect(position.x + 100, position.y + 45, position.x + 100 + bar_width + 3 + offset_shadow, position.y + 68 + offset_shadow, 8, 8);	// mp, �ټ�һ��3�ǲ۵ı�Ե���

    // ����״̬�����۱���
    setfillcolor(RGB(67, 47, 47));
    solidroundrect(position.x + 100, position.y + 10, position.x + 100 + bar_width + 3, position.y + 33, 8, 8);
    solidroundrect(position.x + 100, position.y + 45, position.x + 100 + bar_width + 3, position.y + 68, 8, 8);

    // �������ֵ������
    double hp_bar_width = bar_width * ((max(0, hp)) / 100.0);	//hp���Ϊ100������ʵ���˰ٷֱȡ���max��ֹ���ָ�����Ⱦ��
    double mp_bar_width = bar_width * ((min(100, mp)) / 100.0);	// ��min����Ϊmp����С��0�������100����ʱ��ֹ�����Ⱦ��

    // ����״̬����ֵ
    setfillcolor(RGB(197, 61, 67));		// Ѫ����ɫ
    solidroundrect(position.x + 100, position.y + 10, position.x + 100 + hp_bar_width + 3, position.y + 33, 8, 8);
    setfillcolor(RGB(83, 131, 195));	// ������ɫ
    solidroundrect(position.x + 100, position.y + 45, position.x + 100 + mp_bar_width + 3, position.y + 68, 8, 8);
}
