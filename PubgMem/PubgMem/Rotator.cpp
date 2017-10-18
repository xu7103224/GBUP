
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
