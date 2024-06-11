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
	void loadFromFile(LPCTSTR path, int num)
	{
		img_list.clear();	//��Ϊ����imageָ�룬����clear���Ѿ��ͷ���Դ��
		img_list.resize(num);

		char complete_path[256] = { 0 };
		
		for (int i = 0; i < num; i++)
		{
			sprintf_s(complete_path, sizeof(complete_path), path, i + 1);	// �ز�������1��ʼ����Ϊi + 1
			loadimage(&img_list[i], complete_path);
		}
	}

	//��this��altas�ķ�ת���봫���atlas��
	void saveFlipAtlasTo(Atlas& dst)
	{
		dst.clear();
		for (int i = 0; i < getSize(); i++)
		{
			IMAGE img_filp;
			flip_image(this->getImage(i), &img_filp);
			dst.push_backImage(img_filp);
		}
	}

	//���ͼƬ����
	void clear()
	{
		img_list.clear();
	}

	//��ȡͼƬ���д�С
	int getSize()
	{
		return (int)img_list.size();
	}

	//��ȡ��Ӧ����ͼƬ
	IMAGE* getImage(int index)
	{
		if (index < 0 || index >= (int)img_list.size())
			return nullptr;

		return &img_list[index];
	}

	//ĩβ���ͼƬ��flip atlas�������õ�pushback��
	void push_backImage(const IMAGE img)
	{
		img_list.push_back(img);
		// std::cout << img_list.size() << std::endl;
	}


private:
	
	std::vector < IMAGE > img_list;


};

