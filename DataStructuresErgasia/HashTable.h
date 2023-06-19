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
    std::chrono::milliseconds totalElapsedTime;
    size_t capacity;
	size_t size;

	void resize();
    void insertIntoTable(entry** tableToInsertTo, std::string key);
    void insertIntoTable(entry** tableToInsertTo, std::string key, unsigned int found);
    size_t hash(std::string key);
    size_t hash2(size_t position);

    public: 

    HashTable();
    ~HashTable();

    void insert(std::string key);
    std::string get(std::string key);
    std::string getBuildingTime();
};
#endif