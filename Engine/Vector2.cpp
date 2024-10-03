#include "Vector2.h"
#include <cstddef>

//Vector2

Vector2::Vector2(float VecX, float VecY)
{
	x = VecX;
	y = VecY;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2()
{
	x = NULL;
	y = NULL;
}

//Vector3

Vector3::Vector3(float VecX, float VecY, float VecZ)
{
	x = VecX;
	y = VecY;
	z = VecZ;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::~Vector3()
{
	x = NULL;
	y = NULL;
	z = NULL;
}