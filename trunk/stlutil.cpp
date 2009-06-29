#include <iostream>
#include <iterator>

#include "stlutil.h"

using namespace std;

// Create a vector of strings from an array of char strings
vector<string> vecStringFromArrayStrings(const char *strings[], int numberOfStrings)
{
	return vector<string>(strings, strings + numberOfStrings);
}

// Create a set of strings from an array of char strings
set<string> setStringFromArrayStrings(const char *strings[], int numberOfStrings)
{
	return set<string>(strings, strings + numberOfStrings);
}

// From a single string object return a vector of strings based
// on a specified delimiter
vector<string> stringToVectorStrings(const string &input, const char delimiter)
{
	vector<string> outputStrings;

	size_t begin = 0;

	// case one string only, find will find npos, length is non zero push back whole string 
	// case two strings, find will find first delim, push that, repeat will find npos, push whats left
	// case empty string, find will find npos, but length is zero so just return the empty vector
	// 0123456789
	// ab,cd,ef0
	
	size_t end;

	do
	{
		end = input.find(delimiter, begin);
		if(end != string::npos)
		{
			outputStrings.push_back(input.substr(begin, (end-begin))); 
			begin = end + 1;
		}
		else
		{
			// this is the end then
			if(input.length() > 0)
			{
				outputStrings.push_back(input.substr(begin, input.length() - begin)); 
			}
		}
		

	}
	while(end != string::npos);

	return outputStrings;
};

// From a string delimited by delimiter return a set of strings 
set<string> stringToSetStrings(const string &input, const char delimiter)
{
	vector<string> vectorOfStrings = stringToVectorStrings(input, delimiter);

	set<string> setOfStrings;
	insert_iterator< set<string> > insert_it (setOfStrings,setOfStrings.begin());

	// copy to a set
	copy(vectorOfStrings.begin(), vectorOfStrings.end(), insert_it);

	return setOfStrings;
};

class StringSet
{
	friend ostream &operator << (ostream& os, const StringSet &strSet);

public:
	StringSet(string in)
	{
		m_strSet = stringToSetStrings(in, ' ');
	}

private:
	set<string> m_strSet;
};


void testStringSet()
{
	StringSet ss("some strings where-some-are-multi-word seperated-by not=>space");

	cout << "test:" << endl <<
		ss << endl << ":test" << endl;
}

ostream & operator<<(ostream& output, const StringSet& ss) 
{
	output << "String set with " << ss.m_strSet.size() <<  " elements: ";

	copy(ss.m_strSet.begin(), ss.m_strSet.end(), ostream_iterator<string>(cout, ", "));

	return output;
}
