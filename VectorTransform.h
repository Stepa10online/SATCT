#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

struct VectorTransform
{
public:
	float PosX;
	float PosY;
	float Sin;
	float Cos;

	VectorTransform(Vector2f position, float angle)
	{
		this->PosX = position.x;
		this->PosY = position.y;
		this->Sin = sin(angle);
		this->Cos = cos(angle);
	}
	VectorTransform(float x,float y, float angle=0)
	{
		this->PosX = x;
		this->PosY = y;
		this->Sin = sin(angle);
		this->Cos = cos(angle);
	}
};

