#pragma once
namespace peach
{
struct FVector2
{
	float x;
	float y;

	FVector2(float x, float y)
		:x(x),
		y(y)
	{
	}
	FVector2()
		:x(0),
		y(0)
	{
	}
};

struct IVector2
{
	int x;
	int y;

	IVector2(int x, int y)
		:x(x),
		y(y)
	{
	}
	IVector2()
		:x(0),
		y(0)
	{
	}
};

}