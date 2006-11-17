#pragma once

#include "IObserver.h"

using namespace std;

class ISubject
{
private:
	vector<IObserver *> observers;
public:
	ISubject(void);
	~ISubject(void);
	void attachObserver(IObserver &observer);
	void dettachObserver(IObserver &observer);
protected:
	void notifyObservers();
};
