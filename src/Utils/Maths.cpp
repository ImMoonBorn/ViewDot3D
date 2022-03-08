#include "pch.h"
#include "Maths.h"

namespace Core::Utils
{
	float Maths::Clamp(float value, float min, float max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}
	
	int Maths::Clamp(int value, int min, int max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}
	
	float Maths::Lerp(float from, float to, float t)
	{
		return (1 - t) * from + t * to;
	}
	
	glm::vec2& Maths::Lerp(const glm::vec2& from,const glm::vec2& to, float t)
	{
		glm::vec2 vec;
		vec.x = Lerp(from.x, to.x, t);
		vec.y = Lerp(from.y, to.y, t);
		return vec;
	}
	
	float Maths::RandomFloat(float min, float max)
	{
		int range = (int)max - (int)min;
		return min + (rand() % range);
	}
}