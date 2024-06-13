#pragma once

#include <graphics.h>

#include "Camera.h"

#pragma comment(lib, "Msimg32.lib")

// ��ת��һ������ͼƬ�����浽�ڶ�������ͼƬ
void flip_image(IMAGE* src, IMAGE* dst);

void putimage_alpha(int x, int y, IMAGE* img);

void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);

void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y);

void line_alpha(const Camera& camera, int x1, int y1, int x2, int y2);

void white_image(IMAGE* src, IMAGE* dst);
