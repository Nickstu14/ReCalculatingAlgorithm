#ifndef _RANDOM_H_
#define _RANDOM_H_
//#include "ObjectList.h"

class Random 
{
public:
	Random() = default;
	~Random();

	float RandGen(int min, int max)
	{
		int pos;
		do
		{
			pos = rand() % max;
		} while (pos <= min);

		return pos + 0.5;
	}

};

#endif