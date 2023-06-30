#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>
#include <string>

class HashTable{
    private:
    struct entry
	{
		std::string key;
		unsigned int found;
        bool occupied =  false;
	};

	entry **array;
    std::chrono::nanoseconds totalElapsedTime;
    size_t capacity;
	size_t size;

    int compare(std::string s1, std::string s2);
	void calculateTime(chrono::steady_clock::time_point startTime);

	void resize();
    void insertIntoTable(entry** tableToInsertTo, std::string key, unsigned int found);
    size_t hash(std::string key);
    size_t hash2(size_t position);

    public: 
    HashTable();

    void insert(std::string key);
    std::string get(std::string key);
    std::string getBuildingTime();

    ~HashTable();
};
#endif