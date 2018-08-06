/*
 * @file/Tools/StateMachine/StateMachine.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "StateMachine.h"

void StateMachine::switchState()
{
	for(auto  transitionList : currentState->transition)
	{
//		if(transitionList->condition())
//			currentState = states[transitionList->destination];
	}



}
void StateMachine::update()
{
	switchState();

	currentState->update();
	currentState->onEnter();
	currentState->onEnter();

}


