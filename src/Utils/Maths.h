#pragma once
#include <glm/glm.hpp>

namespace Core::Utils
{
	struct Maths
	{
		static float Clamp(float value, float min, float max);
		static int Clamp(int value, int min, int max);
		static float Lerp(float from, float to, float t);
		static glm::vec2& Lerp(const glm::vec2& from,const glm::vec2& to, float t);
		static float RandomFloat(float min, float max);
	};
}