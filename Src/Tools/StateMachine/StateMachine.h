/*
 * @file/Tools/StateMachine/StateMachine.h
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "AbstractState.h"
#include <map>
#include <memory>
#include "AbstractTransition.h"

class StateMachine {
public:
//  	StateMachine();
//	virtual ~StateMachine();


	void switchState();
	void update();;

  std::map<std::string, std::shared_ptr<AbstractState>> states;


private:
	AbstractState *currentState;
	AbstractTransition *currentTransition;
};

#endif /* STATEMACHINE_H_ */
