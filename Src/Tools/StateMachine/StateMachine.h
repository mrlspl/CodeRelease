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

	void switchState();
	void update();
	void addState(std::string id, AbstractState *state);
	void setState(std::string id);
	std::string getCurrentStateId();



private:
  std::map<std::string, std::unique_ptr<AbstractState> > states;
	std::string currentStateId;
};

#endif /* STATEMACHINE_H_ */
