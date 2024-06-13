#pragma once

#include <graphics.h>
#include <vector>

#include <iostream>

#include "Tools.h"

class Atlas
{
public:
	Atlas() = default;

	~Atlas() = default;

	//���ļ��м������ͼƬ
	void loadFromFile(LPCTSTR path, int num);

	//��this��altas�ķ�ת���봫���atlas��
	void saveFlipAtlasTo(Atlas& dst);

	//���ͼƬ����
	void clear();

	//��ȡͼƬ���д�С
	int getSize();

	//��ȡ��Ӧ����ͼƬ
	IMAGE* getImage(int index);

	//ĩβ���ͼƬ��flip atlas�������õ�pushback��
	void push_backImage(const IMAGE img);

private:
	
	std::vector < IMAGE > img_list;

};

