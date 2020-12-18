#pragma once

#include <chrono>

class Timer {
	static Timer *m_instance;


	std::chrono::steady_clock::time_point begin;

public:
	static Timer *getInstance() {
		if (!m_instance)
			m_instance = new Timer;
		return m_instance;
	}

	void Reset()
	{
		begin = std::chrono::steady_clock::now();
	}

	float getTimePassedInSec()
	{
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		float timePassed = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0f;

		return timePassed;
	}
};

Timer *Timer::m_instance = 0;