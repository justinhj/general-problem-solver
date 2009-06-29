// GPS 
// Justin Heyes-Jones
// GPS is an instance of single problem solver

#include <iostream>
#include <iterator>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>

#include <boost/bind.hpp>

using namespace std;

#include <gps.h>

// Returns whether condition is a member of the given set
// this is used by GPS and Operator classes so it's global
bool conditionIsMember(Condition cond, const ConditionSet &conditionSet)
{
	ConditionSet::const_iterator iter = conditionSet.find(cond);
	return iter != conditionSet.end();
}

// GPS member functions

// Constructor
GPS::GPS()
{
}

GPS::~GPS()
{
	m_state.clear();
	m_operators.clear();
	m_goals.clear();
};

// Remove all conditions, goals and operators
void GPS::reset()
{
	m_state.clear(); 
	m_operators.clear();
	m_goals.clear();
}

// Start the gps with the current set of operators, goals and state
bool GPS::solve()
{
	bool success = true;

	// If we can achieve each goal return true

	vector<Condition>::iterator iter = m_goals.begin();

	while(iter != m_goals.end())
	{
		if(!achieve((*iter)))
		{
			success = false;
			break;
		}

		iter ++;
	}

	cout << "Success: " << success << endl;

	return success;
}

// Add a condition to the current state
void GPS::addCondition(Condition condition)
{
	m_state.insert(condition);
}

// Add a goal for the GPS
void GPS::addGoal(Condition goal)
{
	m_goals.push_back(goal);
}

// Add an operator
void GPS::addOperator(Operator oper)
{
	m_operators.push_back(oper);
}

void GPS::viewOperators() const
{
	copy(m_operators.begin(), m_operators.end(), ostream_iterator<Operator>(cout, "\n"));
}

// Constructor for Operator
Operator::Operator(Action action, 
						 const ConditionSet &preConds, 
						 const ConditionSet &adds, 
						 const ConditionSet &removes)
{
	m_action = action;
	m_preConds = preConds;
	m_adds = adds;
	m_removes = removes;
}

// Destructor for an operator
Operator::~Operator()
{
	m_preConds.clear();
	m_adds.clear();
	m_removes.clear();
}

// True if this condition is added by the operator
bool Operator::isAppropriate(Condition condition) 
{
	return conditionIsMember(condition, m_adds);
}

// Output operator
ostream & operator<<(ostream& output, const Operator& op) 
{
	output << "Action: " << op.m_action << endl;

	ConditionSet::const_iterator iter = op.m_preConds.begin();

	output << "Preconditions:" << endl;

	while(iter != op.m_preConds.end())
	{
		output << "\t" << (*iter) << endl;
		iter++;
	}

	output << "Add conditions:" << endl;

	iter = op.m_adds.begin();

	while(iter != op.m_adds.end())
	{
		output << "\t" << (*iter) << endl;
		iter++;
	}

	output << "Remove conditions:" << endl;

	iter = op.m_removes.begin();

	while(iter != op.m_removes.end())
	{
		output << "\t" << (*iter) << endl;
		iter++;
	}

	return output;
}

// If a goal is already achieved or there is an operator that can
// that can bring it about, then achieve the goal
bool GPS::achieve(Condition goal)
{
	bool achieved = false;

    cout << "Achieve called: " << goal << endl;

	if(conditionIsMember(goal, m_state))
	{
		cout << "Already in state" << endl;
		achieved = true;
	}
	else
	{
		// Remove any operators that are not appropriate for this goal
		vector<Operator>::iterator newEnd = 
			remove_if(m_operators.begin(), m_operators.end(), !boost::bind(&Operator::isAppropriate, _1, goal));

		// Now try to apply any of these operators
		vector<Operator>::iterator opIter = m_operators.begin();
		
		while(opIter != newEnd)
		{
			if(applyOp((*opIter)))
			{
				achieved = true;
				break;
			}

			opIter ++;
		}
	}
	
	return achieved;
}

void GPS::viewState()
{
	cout << "State: "; 
	copy(m_state.begin(), m_state.end(), ostream_iterator<Condition>(cout, ", "));
	cout << endl;
}

// If the operation is applicable we apply it
// and modify the state accordingly
bool GPS::applyOp(Operator op)
{
	// Check that we can achieve each precondition
	// return false otherwise

	cout << "applyOp: " << op.m_action << endl;
	viewState();

	ConditionSet::iterator iter = op.m_preConds.begin();
	while(iter != op.m_preConds.end())
	{
		if(!achieve((*iter)))
		{
			return false;
		}

		iter ++;
	}

	// We satisfied all the preconditions

	cout << "Executing: " << op.m_action << endl;

	// Handle the conditions this operator removes

	iter = op.m_removes.begin();

	while(iter != op.m_removes.end())
	{
		const Condition &condition = (*iter);

		// remove this condition from the current state
		ConditionSet::iterator findIter = m_state.find(condition);

		if(findIter != m_state.end())
		{
			m_state.erase(condition);
		}

		iter ++;
	}
	
	// And add the conditions it adds

	m_state.insert(op.m_adds.begin(),op.m_adds.end());

	return true;
}
	





