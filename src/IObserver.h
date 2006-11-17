#pragma once

class ISubject;

class IObserver
{
public:
	IObserver(void) {}
	~IObserver(void) {}
	virtual void update(const ISubject &subject) {};
};
