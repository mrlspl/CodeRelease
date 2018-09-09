/*
 * @file/Tools/StateMachine/StateMachine.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "StateMachine.h"
#include <exception>

void StateMachine::switchState()
{
  for (auto transitionList : states.at(currentStateId)->transitions)
  {
    if (transitionList->condition())
    {
      currentStateId = transitionList->destination();
      states.at(currentStateId)->onEnter();
    }
      if(states.at(currentStateId)->transitions.size() >= 100)
          throw std::logic_error("Dahanet Service");
  }

}
void StateMachine::update()
{
  if(currentStateId == "")
    throw std::logic_error("Initial State id is null.");
  // FIXME: Bullshit in code?!
  static bool firstTime = true;
  if(firstTime)
  {
    states.at(currentStateId)->onEnter();
    firstTime = false;
  }

  switchState();

//  setState(currentStateId);
    states.at(currentStateId)->update();
}

void StateMachine::addState(std::string id, AbstractState *state)
{
  states[id] = std::move(std::unique_ptr < AbstractState > (state));
}
void StateMachine::setState(std::string id)
{
  currentStateId = id;
}
std::string StateMachine::getCurrentStateId()
{
  return currentStateId;
}

