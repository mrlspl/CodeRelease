/*
 * @file/Tools/StateMachine/AbstractState.h
 * Base class for all states.
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */
#include <iostream>


#pragma once

#include "AbstractTransition.h"
class AbstractState
{

public :

	virtual void update() = 0;
	virtual void onEnter(){}
	virtual void onExit(){}
	virtual ~AbstractState(){}
	std::vector<AbstractTransition*> transition;

protected:
	std::string stateId;
	AbstractState(std::string id) : stateId(id) {}



};


