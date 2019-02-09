#include "pch.h"
#include "BasicMath.h"
#include <cassert>
// 0 to 8
const float pow2s[] = 
{
	1.00f,		//0
	2.00f,		//1
	4.00f,		//2
	8.00f,		//3
	16.00f,		//4
	32.00f,		//5
	64.00f,		//6
	128.00f,	//7
	256.00f,	//8
};

double math::pow2(const int power)
{
	assert(power < 9);
	return pow2s[power];
}

double math::max(const double a, const double b)
{
	if (a > b) return a;
	return b;
}

int math::avg(const int * array, const int size)
{
	int max, min, result;
	max = math::max(array, size);
	min = math::min(array, size);
	result = (max + min) / 2;
	return result;
}

int math::max(const int * array, const int size)
{
	int result = 0;
	for (int i = 0; i < size; ++i)
	{
		if (result < array[i]) result = array[i];
	}
	return result;
}

int math::min(const int * array, const int size)
{
	int result = 0;
	for (int i = 0; i < size; ++i)
	{
		if (result > array[i]) result = array[i];
	}
	return result;
}
