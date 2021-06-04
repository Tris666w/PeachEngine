#pragma once

template<typename T>
inline T Interpolate(T value1, T value2, float t)
{
	return (1.0f - t) * value1 + t * value2;
}


template<typename T>
inline void Clamp(T& value, T min, T max)
{
	if (value > max)
		value = max;

	if (value < min)
		value = min;
}
