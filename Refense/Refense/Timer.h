#pragma once

#include <chrono>

class Timer 
{

public:
	static Timer& get() {
		static Timer s_Instance;
		return s_Instance;
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

private:
	Timer() {}

	std::chrono::steady_clock::time_point begin;
};
