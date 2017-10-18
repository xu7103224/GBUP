#include "vector3D.h"
#include "FMath.h"

Vector3D::Vector3D() : x(0.f), y(0.f), z(0.f)
{
}

Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

Vector3D::~Vector3D()
{
}

Vector3D Vector3D::operator+(Vector3D v)
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(Vector3D v)
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}