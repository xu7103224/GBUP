#pragma once
#include <math.h>

//Vector3
class Vector3D
{
public:
	Vector3D();

	Vector3D(float _x, float _y, float _z);
	~Vector3D();

	float x;
	float y;
	float z;

	inline float Dot(Vector3D v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3D v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector3D operator+(Vector3D v);

	Vector3D operator-(Vector3D v);
};