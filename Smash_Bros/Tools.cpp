#include "Tools.h"

// ��ת��һ������ͼƬ�����浽�ڶ�������ͼƬ
void flip_image(IMAGE* src, IMAGE* dst)	//source and destination
{
    int w = src->getwidth();
    int h = src->getheight();

    //����dstͼƬ�Ĵ�С
    Resize(dst, w, h);

    //��ȡ��������ͼƬ�����ص����飨DWORD�൱��unsigned long��
    DWORD* src_buffer = GetImageBuffer(src);
    DWORD* dst_buffer = GetImageBuffer(dst);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            //ͼƬbuffer����һά�����ʾ��ά����������Ҫ��һά������ʶ�ά�ķ�ʽ
            int src_index = y * w + x;
            int dst_index = y * w + (w - x - 1);
            dst_buffer[dst_index] = src_buffer[src_index];
        }
    }
}

void putimage_alpha(int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    const Vector2& pos_camera = camera.getPosition();
    AlphaBlend(GetImageHDC(NULL), (int)(x - pos_camera.x), (int)(y - pos_camera.y), w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y)
{
    int w = width > 0 ? width : img->getwidth();
    int h = height > 0 ? height : img->getheight();
    AlphaBlend(GetImageHDC(NULL), dst_x, dst_y, w, h, GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void line_alpha(const Camera& camera, int x1, int y1, int x2, int y2)
{
    const Vector2& pos_camera = camera.getPosition();

    line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}

void white_image(IMAGE* src, IMAGE* dst)
{
    int w = src->getwidth();
    int h = src->getheight();

    Resize(dst, w, h);

    DWORD* src_buffer = GetImageBuffer(src);
    DWORD* dst_buffer = GetImageBuffer(dst);

    for (int i = 0; i < w * h; i++)
    {
        dst_buffer[i] = BGR(RGB(255, 255, 255)) | (src_buffer[i] & 0xFF000000);
        /*
        ����֪ʶ��bufferÿһ��ֵ����8��16����λ��32��2����λ����ɡ��������16����λλ͸���ȣ��������ɸ�λ����λÿ��λ�ֱ�Ϊred green blueɫ��ͨ��ֵ��
        ����(src_buffer[i] & 0xFF000000)�ǻ�ȡsrc_bufferÿһ�����ص�͸���ȣ������͸����������dst_bufferÿһ�����ص�͸���ȡ���BGR��ɶ���͸���ȣ�
        */
    }
}
