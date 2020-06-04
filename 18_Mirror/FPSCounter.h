#ifndef __FPS_COUNTER_H__
#define __FPS_COUNTER_H__

#include <chrono>

class FPSCounter
{
private:
	std::chrono::steady_clock::time_point _last_print;
	std::chrono::steady_clock::time_point _last_delta;
	int _frames;
public:
	FPSCounter() noexcept;

	void tick() noexcept;

	double getDelta() noexcept;
};

#endif