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

	int timer = 0;						// ���Ӳ��ż�ʱ��
	int lifespan = 0;					// ��֡���ӵ��������ڣ�����ʱ����
	int index_frame = 0;				// ��ǰ����֡
	Vector2 position;					// ���ӵ���������λ��
	bool is_valid = true;				// �����Ƿ���Ч�������Ƿ������
	Atlas* atlas = nullptr;				// ���Ӷ���ͼ��

};

