#pragma once

#include <chrono>
#include <iostream>

class Timer {
private:
	std::chrono::steady_clock::time_point _startTimePoint;
public:
	explicit Timer() {
		_startTimePoint = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto finishTimePoint = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = finishTimePoint - _startTimePoint;
		std::cout << "Duration: " << duration.count() << " s" << std::endl;
	}
};