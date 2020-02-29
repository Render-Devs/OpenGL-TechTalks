#pragma once

class Timestep
{
public:
	Timestep(float startupTime, float frameTime = 0.0f) : m_Time(frameTime), m_TimeSinceStartup(startupTime) {}
	operator float() const { return m_Time; }
	float GetSeconds() const { return m_Time; }
	float GetMilliseconds() const { return m_Time * 1000.0f; }
	float GetTimeSinceStart() { return m_TimeSinceStartup; }


	operator float const()
	{
		return m_Time;
	}

private:
	float m_Time;
	float m_TimeSinceStartup;

};

