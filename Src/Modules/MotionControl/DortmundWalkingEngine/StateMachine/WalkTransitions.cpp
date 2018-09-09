/*
 * @file/Tools/StateMachine/Transitions.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "WalkTransitions.h"
#include <iostream>

LeftStepFinish::LeftStepFinish(const SingleSupportLeft& source) :
    source_(source)
{
}
bool LeftStepFinish::condition()
{
  return (source_.counter >= 22);

}
std::string LeftStepFinish::destination() const
{
  return "SingleSupportRight";
}

RightStepFinish::RightStepFinish(const SingleSupportRight& source) :
        source_(source)
{
}
bool RightStepFinish::condition()
{
  return (source_.counter >= 23);
}

std::string RightStepFinish::destination() const
{
  return "SingleSupportLeft";
}


StepPossible::StepPossible(const Pose2f& speed ,LegPoint& legPoint) :
    _legPoint(legPoint)
{
//  destination = "SingleSupportRight";
}
bool StepPossible::condition()
{
  return false;

}

IsReady::IsReady(const Ready& source) : source_(source)
{}
bool IsReady::condition()
{
    return (source_.counter >= 100);
}
std::string IsReady::destination() const
{
  return "SingleSupportLeft";
}
//
//bool KickRequestRight::condition()
//{
//  return false;
//
//}
//bool KickRequestLeft::condition()
//{
//  return false;
//}
//bool KickFinish::condition()
//{
//  return false;
//}
//bool RobotIsFalling::condition()
//{
//  return false;
//}
//bool RobotRecoverd::condition()
//{
//  return false;
//}
