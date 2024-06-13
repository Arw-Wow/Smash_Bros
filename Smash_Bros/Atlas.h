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
	void loadFromFile(LPCTSTR path, int num);

	//将this的altas的翻转存入传入的atlas里
	void saveFlipAtlasTo(Atlas& dst);

	//清空图片序列
	void clear();

	//获取图片序列大小
	int getSize();

	//获取对应索引图片
	IMAGE* getImage(int index);

	//末尾添加图片（flip atlas方法会用到pushback）
	void push_backImage(const IMAGE img);

private:
	
	std::vector < IMAGE > img_list;

};

