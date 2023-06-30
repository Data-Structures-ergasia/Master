#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>


namespace constants{
    static std::string const INPUT_FILE_NAME = "small-file.txt";
    static std::string const OUTPUT_FILE_NAME = "output.txt";

    static std::string const ELLAPSED_TIME_IN = "Elapsed time in ";
    static std::string const BUILDING_TIME = "Building time in ";


    static std::string const MS = "ms";
    static std::string const MILLISECONDS = "milliseconds: ";

    static std::string const NS = "ns";
    static std::string const NANOSECONDS = "nanosecods: ";
    
    static std::string const SEC = "sec";
    static std::string const SECONDS = "seconds: ";

    static std::string const HASH_TABLE_BUILD_TIME_UNIT = MS;
    static std::string const UNSORTED_ARRAY_BUILD_TIME_UNIT = MS;
    static std::string const SORTED_ARRAY_BUILD_TIME_UNIT = MS;
    static std::string const BINARY_TREE_BUILD_TIME_UNIT = MS;
    static std::string const AVL_TREE_BUILD_TIME_UNIT = MS;

    static std::string const HASH_TABLE_SEARCH_TIME_UNIT = MS;
    static std::string const UNSORTED_ARRAY_SEARCH_TIME_UNIT = MS;
    static std::string const SORTED_ARRAY_SEARCH_TIME_UNIT = MS;
    static std::string const BINARY_TREE_SEARCH_TIME_UNIT = MS;
    static std::string const AVL_TREE_SEARCH_TIME_UNIT = MS;

    static std::string const NEWLINE = "\n";
    static std::string const TAB = "\t";

    static std::string const HEADLINE_FIRST_PART = NEWLINE + NEWLINE + TAB + TAB;
    static std::string const HEADLINE_SECOND_PART = NEWLINE + NEWLINE;

    static std::string const UNSORTED_ARRAY = "Unsorted Array";
    static std::string const SORTED_ARRAY = "Sorted Array";
    static std::string const HASH_TABLE = "Hash Table";
    static std::string const BINARY_TREE = "Binary Tree";
    static std::string const AVL_TREE = "AVL Tree";


    static std::string const NOT_ENOUGH_MEMORY = "Not enough memory!";
    static std::string const NOT_ENOUGH_MEMORY_TO_RESIZE = "Not enough memory to resize!";
    static std::string const COULD_NOT_OPEN = "Could not open ";    

    static std::string const KEY = "Key : \"";
    static std::string const RIGHT_QUOTATION_MARK = "\"";
    static std::string const WAS_FOUND = " was found ";
    static std::string const WAS_NOT_FOUND = " was not found!";
    static std::string const TIMES = " times!";

    static std::string const EMPTY = ""; 

    static int const Q_SIZE = 1000;
    static int const ARRAY_SIZE = 10000000;
    static float const LOAD_FACTOR = 0.75;
}

#endif