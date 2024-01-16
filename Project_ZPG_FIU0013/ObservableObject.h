#pragma once
/**
 *
 * @brief ObservableObject header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Observer.h"

class ObservableObject {
protected:
	std::vector<Observer*> observers;
public:
	virtual void addObserver(Observer* observer);
	virtual void deleteObserver(Observer* observer);
	virtual void notifyObservers(int index) = 0;
};
