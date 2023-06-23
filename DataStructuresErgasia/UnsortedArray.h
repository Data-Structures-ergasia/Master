#ifndef UNSORTEDARRAY_H
#define UNSORTEDARRAY_H
#include <stdlib.h>


class UnsortedArray
{
private:
	struct entry
	{
		std::string key;
		unsigned int found;
	};

    std::chrono::nanoseconds totalElapsedTime;
	entry **array;
	size_t capacity;
	size_t size;

	int compare(std::string s1, std::string s2);
	void calculateTime(std::chrono::steady_clock::time_point startTime);
	void insertIntoTable(entry** tableToInsertTo, std::string key, unsigned int found);
	void insertIntoTable(entry** tableToInsertTo, std::string key);
	void resize();
public:
	UnsortedArray();

	void insert(std::string key);
	std::string find(std::string key);
    std::string getBuildingTime();

	~UnsortedArray();
};

#endif