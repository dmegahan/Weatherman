#ifndef ACTION_H
#define ACTION_H

#define DEFAULT_COST 1

class Action{
protected:
	int cost;
public:
	Action();
	//~Action();
	virtual bool execute(){ return true; }
};

#endif