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

    std::chrono::milliseconds totalElapsedTime;
	entry **array;
	size_t capacity;
	size_t size;

	void resize();
	void insertIntoTable(entry** tableToInsertTo, std::string key, unsigned int found);
	void insertIntoTable(entry** tableToInsertTo, std::string key);
public:
	UnsortedArray();

	void insert(std::string key);
	std::string find(std::string key);
    std::string getBuildingTime();

	~UnsortedArray();
};

#endif