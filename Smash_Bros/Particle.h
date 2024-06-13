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

	int timer = 0;						// ���Ӳ��ż�ʱ��
	int lifespan = 0;					// ��֡���ӵ��������ڣ�����ʱ����
	int index_frame = 0;				// ��ǰ����֡
	Vector2 position;					// ���ӵ���������λ��
	bool is_valid = true;				// �����Ƿ���Ч�������Ƿ������
	Atlas* atlas = nullptr;				// ���Ӷ���ͼ��

};

