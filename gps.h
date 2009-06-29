// Header for general problem solver in cpp

#ifndef GPS_H
#define GPS_H

// Condition and Action are just strings
// though they could be changed to be more complex objects
typedef string Condition;
typedef string Action;

typedef set<Condition> ConditionSet;

// An operator represents an action when the preConds are met
// adding the conditions that arise when the action is performed
// and removing the conditions that cease when the action 
// is performed

class Operator
{
	friend ostream &operator << (ostream& os, const Operator &op);

 public:
	Operator(Action action, 
				const ConditionSet &preConds, 
				const ConditionSet &adds, 
				const ConditionSet &removes);

	virtual ~Operator();

	bool isAppropriate(Condition goal); 
	bool temp() { return true; }

 public:
	Action m_action; 
	ConditionSet m_preConds;
	ConditionSet m_adds;
	ConditionSet m_removes;


};

class GPS
{
public: 
	GPS();
	virtual ~GPS();

	void reset();

	void addOperator(Operator op);

	void addGoal(Condition goal);

	void addCondition(Condition condition);

	// debug
	void viewOperators() const;
	void viewState();

	bool solve();

	bool achieve(Condition goal);

	bool applyOp(Operator op);

private:
	vector<Operator> m_operators;
	vector<Condition> m_goals;
	ConditionSet m_state;

};

bool conditionIsMember(Condition cond, const ConditionSet &conditionSet);

#endif
