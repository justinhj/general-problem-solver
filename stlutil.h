#ifndef STL_UTIL_H
#define STL_UTIL_H

// Some utility functions for using STL

#include <string>
#include <vector>
#include <set>

// Calculate the size of an array 
#define ARRAY_SIZE(ar) (sizeof(ar) / sizeof(ar[0]))

// Macros to make vector and set of strings from an array of char strings
#define MK_STR_VECTOR(arrayStrings) vecStringFromArrayStrings(arrayStrings, ARRAY_SIZE(arrayStrings))
#define MK_STR_SET(arrayStrings) setStringFromArrayStrings(arrayStrings, ARRAY_SIZE(arrayStrings))

// Make an empty set of strings
#define MK_STR_SET_EMPTY set<string>()

std::vector<std::string> vecStringFromArrayStrings(const char *strings[], int numberOfStrings);
std::set<std::string> setStringFromArrayStrings(const char *strings[], int numberOfStrings);
std::vector<std::string> stringToVectorStrings(const std::string &input, const char delimiter);
std::set<std::string> stringToSetStrings(const std::string &input, const char delimiter);

#endif
