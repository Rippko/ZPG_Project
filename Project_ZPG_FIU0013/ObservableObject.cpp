#include "ObservableObject.h"

void ObservableObject::addObserver(Observer* observer)
{
	observers.push_back(observer);
}

void ObservableObject::deleteObserver(Observer* observer)
{
	observers.erase(find(observers.begin(), observers.end(), observer));
}
