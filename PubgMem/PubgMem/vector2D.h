#pragma once

class Vector2D
{
public:
	Vector2D();

	Vector2D(float _x, float _y);
	~Vector2D();
	/** Vector's X component. */
	float x;

	/** Vector's Y component. */
	float y;
};
