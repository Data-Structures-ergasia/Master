#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H
#include <stdlib.h>

class SortedArray
{
private:
	struct entry
	{
		std::string key;
		unsigned int found;
	};

    std::chrono::milliseconds totalElapsedTime;
	entry **array;
	long long int capacity;
	long long int size;

	int compare(std::string s1, std::string s2);
	long long int findPositionOf(std::string key);
	void resize();
public:
	SortedArray();

	void insert(std::string key);
	std::string find(std::string key);
    std::string getBuildingTime();
	std::string get(long long int i);
	long long int getSize();
	~SortedArray();
};

#endif