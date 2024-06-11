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

	//从文件中加载添加图片
	void loadFromFile(LPCTSTR path, int num)
	{
		img_list.clear();	//因为不是image指针，所以clear就已经释放资源了
		img_list.resize(num);

		char complete_path[256] = { 0 };
		
		for (int i = 0; i < num; i++)
		{
			sprintf_s(complete_path, sizeof(complete_path), path, i + 1);	// 素材命名从1开始，故为i + 1
			loadimage(&img_list[i], complete_path);
		}
	}

	//将this的altas的翻转存入传入的atlas里
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

	//清空图片序列
	void clear()
	{
		img_list.clear();
	}

	//获取图片序列大小
	int getSize()
	{
		return (int)img_list.size();
	}

	//获取对应索引图片
	IMAGE* getImage(int index)
	{
		if (index < 0 || index >= (int)img_list.size())
			return nullptr;

		return &img_list[index];
	}

	//末尾添加图片（flip atlas方法会用到pushback）
	void push_backImage(const IMAGE img)
	{
		img_list.push_back(img);
		// std::cout << img_list.size() << std::endl;
	}


private:
	
	std::vector < IMAGE > img_list;


};

