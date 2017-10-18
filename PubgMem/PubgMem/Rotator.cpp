
#include "vector3D.h"
#include "Rotator.h"
#include "FMath.h"

Rotator::Rotator()
{
}

Rotator::Rotator(float Pitch, float Yaw, float Roll)
{
}

Rotator::~Rotator()
{
}

Vector3D Rotator::Vector() const
{
	float CP, SP, CY, SY;
	FMath::SinCos(&SP, &CP, FMath::DegreesToRadians(Pitch));
	FMath::SinCos(&SY, &CY, FMath::DegreesToRadians(Yaw));
	Vector3D V = Vector3D(CP*CY, CP*SY, SP);

	return V;
}

void Rotator::GetAxes(Vector3D &x, Vector3D &y, Vector3D &z)
{
	D3DMATRIX m = FMath::Matrix(*this);

	x = Vector3D(m._11, m._12, m._13);
	y = Vector3D(m._21, m._22, m._23);
	z = Vector3D(m._31, m._32, m._33);
}