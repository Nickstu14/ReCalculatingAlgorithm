#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
	m_start = steady_clock::now(); //store current time
}

Timer::~Timer()
{

}

void Timer::Time(float _maxTime)
{
	m_end = steady_clock::now();//set end value as old current time

	do
	{
		m_start = steady_clock::now(); //update current time
		m_totalTime = m_start - m_end; //total time elapsed
		// if the total time is the same as max time set then break
		if (_maxTime <= m_totalTime.count())
		{
			break;
		}
	} while (1);
}


