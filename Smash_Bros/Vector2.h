#pragma once

#include <cmath>

// ��ά�����࣬��double��ȷ��
class Vector2
{
public:

	double x = 0;
	double y = 0;

public:

	Vector2(double x = 0, double y = 0) : x(x), y(y) { }
	~Vector2() = default;

	Vector2 operator + (const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	void operator += (const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	Vector2 operator - (const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	void operator -= (const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	double operator * (const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	Vector2 operator * (double val) const
	{
		return Vector2(x * val, y * val);
	}

	void operator *= (double val)
	{
		x *= val;
		y *= val;
	}

	//��ȡlength����
	double length()
	{
		return sqrt(x * x + y * y);
	}

	// normalize��׼������λ����
	Vector2 normalize()
	{
		double len = length();

		if (len == 0)
			return Vector2(0, 0);

		return Vector2(x / len, y / len);
	}


};

