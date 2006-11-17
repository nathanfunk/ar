#include <vector>
#include "IObserver.h"
#include "ISubject.h"


ISubject::ISubject(void)
{
}

ISubject::~ISubject(void)
{
}

void ISubject::attachObserver(IObserver &observer)
{
	observers.push_back(&observer);
}

void ISubject::dettachObserver(IObserver &observer)
{
	
}

void ISubject::notifyObservers()
{
	unsigned int i;
	for (i=0; i<observers.size(); i++) {
		observers[i]->update(*this);
	}
}