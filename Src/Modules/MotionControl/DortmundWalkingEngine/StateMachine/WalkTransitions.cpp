/*
 * @file/Tools/StateMachine/Transitions.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "WalkTransitions.h"

StepFinish::StepFinish(const FootStepsPoint& footStepsPoint, LegPoint& legPoint) :
    _legPoint(legPoint), _footStepsPoint(footStepsPoint)
{
}
bool StepFinish::condition()
{
//  if (!singleSupportLeft.legPointsFile.empty()) return false;
//  {
//    return true;
//  }
//
  return false;

}
StepPossible::StepPossible(const FootStepsPoint& footStepsPoint,
    LegPoint& legPoint) :
    _legPoint(legPoint), _footStepsPoint(footStepsPoint)
{
  destination = "SingleSupportRight";
}
bool StepPossible::condition()
{
////  if (~singleSupportLeft.legPointsFile.empty()
////      /*&& _footStepsPoint.footStepForward*/ && motionRequest.walkRequest.isReady)
////      //&& _legPoint.isOnFloor[1])
//  {
//    return true;
//  }
////  else if (!singleSupportLeft.legPointsFile.empty()
////      /*&&_footStepsPoint.footStepForward*/&& motionRequest.walkRequest.isReady)
//////      && _legPoint.isOnFloor[0])
//  {
//    return true;
//  }
  return false;

}

bool IsReady::condition()
{
//  if (motionRequest.walkRequest.isReady)
//  {
//    std::cout << __LINE__ << __FILE__ << "come here and fix this data "
//        << std::endl;
////    destination = new SingleSupportLeft;
//    return true;
//  }
  return false;
}

bool KickRequestRight::condition()
{
  return false;

}
bool KickRequestLeft::condition()
{
  return false;
}
bool KickFinish::condition()
{
  return false;
}
bool RobotIsFalling::condition()
{
  return false;
}
bool RobotRecoverd::condition()
{
  return false;
}
