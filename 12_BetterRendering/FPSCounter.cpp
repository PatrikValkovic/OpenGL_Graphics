#include "FPSCounter.h"

#include <iostream>

using namespace std;

FPSCounter::FPSCounter() noexcept:
	_last_print(chrono::steady_clock::now()), 
	_frames(0), 
	_last_delta(chrono::steady_clock::now() + chrono::hours(24))
{}

void FPSCounter::tick() noexcept
{
	_frames++;
	if (_last_print + chrono::seconds(1) < chrono::steady_clock::now()) {
		cout << "FPS: " << _frames << endl;
		_frames = 0;
		_last_print = chrono::steady_clock::now();
	}
}

double FPSCounter::getDelta() noexcept
{
	chrono::steady_clock::time_point old = _last_delta;
	_last_delta = chrono::steady_clock::now();

	if (_last_delta < old) {
		return 0.0;
	}
	return chrono::duration<float>(_last_delta - old).count();
}
