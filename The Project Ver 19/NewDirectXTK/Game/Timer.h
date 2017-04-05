#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <iostream>
class Timer
{
public:
	Timer();
	~Timer();

	void Time(float _maxTime);



private:
	std::chrono::steady_clock::time_point m_end;
	std::chrono::steady_clock::time_point m_start;

	std::chrono::duration<float> m_totalTime;
};




#endif;