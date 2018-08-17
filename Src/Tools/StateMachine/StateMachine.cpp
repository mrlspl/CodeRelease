/*
 * @file/Tools/StateMachine/StateMachine.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "StateMachine.h"
#include <exception>

void StateMachine::switchState()
{
  for (auto transitionList : currentState->transitions)
  {
    if (transitionList->condition())
    {
      currentState = std::move(states[transitionList->destination()]);
      currentStateId = transitionList->destination();
      std::cout << "currentStateID                " << currentStateId << std::endl;
      currentState->onEnter();
    }
  }

}
void StateMachine::update()
{
  if (currentState == NULL)
    throw std::logic_error("Initial State is not set to state machine.");
  if(currentStateId == "")
    throw std::logic_error("Initial State id is null.");
  // FIXME: Bullshit in code?!
  static bool firstTime = true;
  if(firstTime)
  {
    currentState->onEnter();
    firstTime = false;
  }


  switchState();

  currentState->update();
}

void StateMachine::addState(std::string id, AbstractState *state)
{
  states[id] = std::move(std::unique_ptr < AbstractState > (state));
}
void StateMachine::setState(std::string id)
{
  currentState = std::move(states[id]);
  currentStateId = id;
}
std::string StateMachine::getCurrentStateId()
{
  return currentStateId;
}

