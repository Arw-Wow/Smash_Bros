#pragma once

#include "Vector2.h"
#include "Tools.h"
#include "Atlas.h"

class Particle
{
public:
	Particle() = default;
	~Particle() = default;

	Particle(const Vector2& position, Atlas* atlas, int lifespan) : position(position), atlas(atlas), lifespan(lifespan) { }

	void set_atlas(Atlas* new_atlas)
	{
		atlas = new_atlas;
	}

	void set_lifespan(int ms)
	{
		lifespan = ms;
	}

	void set_position(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	bool check_valid() const
	{
		return is_valid;
	}

	void on_update(int delta)
	{
		timer += delta;

		if (timer >= lifespan)
		{
			timer -= lifespan;
			index_frame++;
			if (index_frame >= atlas->getSize())
			{
				index_frame = atlas->getSize() - 1;
				is_valid = false;
			}
		}
	}

	void on_draw(const Camera& camera) const
	{
		putimage_alpha(camera, position.x, position.y, atlas->getImage(index_frame));
	}

private:

	int timer = 0;						// 粒子播放计时器
	int lifespan = 0;					// 单帧粒子的生命周期（持续时长）
	int index_frame = 0;				// 当前播放帧
	Vector2 position;					// 例子的世界坐标位置
	bool is_valid = true;				// 粒子是否有效（生命是否结束）
	Atlas* atlas = nullptr;				// 粒子动画图集

};

