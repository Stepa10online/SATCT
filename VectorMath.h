#pragma once

//#include "Vector2f.h"
#include<SFML/Graphics.hpp>
#include <math.h>

#include "VectorTransform.h"

using namespace sf;

static class VectorMath
{
public:
	VectorMath() {};
		
	static float Length(Vector2f v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}
	static float Distance(Vector2f a, Vector2f b)
	{
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return sqrt(dx * dx + dy * dy);
	}
	static float Dot(Vector2f a, Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}
	static Vector2f Normalize(Vector2f v)
	{
		float len = Length(v);
		return Vector2f(v.x / len, v.y / len);
	}
	static float Cross(Vector2f a, Vector2f b)
	{
		return a.x * b.y - a.y * b.x;
	}
	void Step(float time)
	{

	}
	VectorTransform Transform(Vector2f v, VectorTransform transform)
	{
		return {
			transform.Cos * v.x - transform.Sin * v.y + transform.PosX,
			transform.Sin * v.x + transform.Cos * v.y + transform.PosY
		};
	}
};