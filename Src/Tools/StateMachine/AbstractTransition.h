/*
 * @file/Tools/StateMachine/AbstractTransition.h
 * Base class for Transitions of All States
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */


#ifndef ABSTRACTTRANSITION_H_
#define ABSTRACTTRANSITION_H_
#include <vector>


class AbstractState;
class AbstractTransition {
public:
	virtual ~AbstractTransition() {}
	virtual bool condition() = 0;
	std::string destination;
};

#endif /* ABSTRACTTRANSITION_H_ */
