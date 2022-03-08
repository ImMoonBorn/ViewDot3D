#pragma once

namespace Core
{
	class Time
	{
	private:
		static float m_DeltaTime;
		friend class Application;
	public:
		static float DeltaTime() { return m_DeltaTime;  }
	};
}