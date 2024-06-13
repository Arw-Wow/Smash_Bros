#pragma once

#include "Vector2.h"
#include "Tools.h"
#include "Atlas.h"

class Particle
{
public:
	Particle() = default;

	~Particle() = default;

	Particle(const Vector2& position, Atlas* atlas, int lifespan);

	void set_atlas(Atlas* new_atlas);

	void set_lifespan(int ms);

	void set_position(int x, int y);

	bool check_valid() const;

	void on_update(int delta);

	void on_draw(const Camera& camera) const;

private:

	int timer = 0;						// 粒子播放计时器
	int lifespan = 0;					// 单帧粒子的生命周期（持续时长）
	int index_frame = 0;				// 当前播放帧
	Vector2 position;					// 例子的世界坐标位置
	bool is_valid = true;				// 粒子是否有效（生命是否结束）
	Atlas* atlas = nullptr;				// 粒子动画图集

};

