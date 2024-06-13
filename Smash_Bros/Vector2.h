#pragma once

#include <cmath>

// ��ά�����࣬��double��ȷ��
class Vector2
{
public:

	double x = 0;
	double y = 0;

public:

	Vector2(double x = 0, double y = 0);

	~Vector2() = default;

	Vector2 operator + (const Vector2& other) const;

	void operator += (const Vector2& other);

	Vector2 operator - (const Vector2& other) const;

	void operator -= (const Vector2& other);

	double operator * (const Vector2& other) const;

	Vector2 operator * (double val) const;

	void operator *= (double val);

	void operator *= (const Vector2& other);

	//��ȡlength����
	double length();

	// normalize��׼������λ����
	Vector2 normalize();

};

