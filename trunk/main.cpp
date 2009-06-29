////////////////////////////////////////////////////////////////////////////////
// General Problem Solver
// Based on Chapter 4 "GPS: The general problem solver" of Peter Norvig's
// Paradigms of AI Programming 
// CPP version by Justin Heyes-Jones
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <iterator>

using namespace std;

#include <gps.h>
#include <stlutil.h>

void example1()
{
	GPS gps;

	// Add the operators 
	gps.addOperator(Operator("drive-son-to-school",  // Action
							 stringToSetStrings("son-at-home car-works", ' '), // pre conditions
							 stringToSetStrings("son-at-school", ' '), // adds
							 stringToSetStrings("son-at-home", ' '))); // removes
	
	gps.addOperator(Operator("shop-installs-battery", 
							 stringToSetStrings("car-needs-battery shop-knows-problem shop-has-money", ' '), 
							 stringToSetStrings("car-works", ' '),
							 MK_STR_SET_EMPTY));
	
	gps.addOperator(Operator("tell-shop-problem", 
							 stringToSetStrings("in-communication-with-shop", ' '),
							 stringToSetStrings("shop-knows-problem", ' '),
							 MK_STR_SET_EMPTY));
	
	gps.addOperator(Operator("telephone-shop", 
							 stringToSetStrings("know-phone-number", ' '),
							 stringToSetStrings("in-communication-with-shop", ' '),
							 MK_STR_SET_EMPTY));
	
	gps.addOperator(Operator("look-up-number",
							 stringToSetStrings("have-phone-book", ' '),
							 stringToSetStrings("know-phone-number", ' '), 
							 MK_STR_SET_EMPTY));
	
	gps.addOperator(Operator("give-shop-money", 		
							 stringToSetStrings("have-money", ' '),
							 stringToSetStrings("shop-has-money", ' '),
							 stringToSetStrings("have-money", ' ')));

	gps.addCondition(Condition("son-at-home"));
	gps.addCondition(Condition("car-needs-battery"));
	gps.addCondition(Condition("have-money"));
	gps.addCondition(Condition("have-phone-book"));

	gps.addGoal(Condition("son-at-school"));

	gps.solve();

}

int main()
{

	example1();

	return 0;
}

