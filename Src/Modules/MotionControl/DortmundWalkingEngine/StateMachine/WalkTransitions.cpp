/*
 * @file/Tools/StateMachine/Transitions.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "WalkTransitions.h"
#include "WalkPhases.h"
#include <iostream>

LeftStepFinish::LeftStepFinish(const SingleSupportLeft& source) :
    source_(source)
{
}
bool LeftStepFinish::condition()
{
//  std::cout << "source   " << (source_.counter > 50) << std::endl;
  return source_.counter > 50;

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
  return source_.counter > 50;
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
//  if (
//      /*&& _footStepsPoint.footStepForward*/ )
//      //&& _legPoint.isOnFloor[1])
//  {
//    return true;
//  }
//  else if ()
//  {
//    return true;
//  }
  return false;

}

bool IsReady::condition()
{
  if (true /* mean ready command from behavior*/)
  {
    std::cout << __LINE__ << __FILE__ << "come here and fix this data "
        << std::endl;
    return true;
  }
  return false;
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
