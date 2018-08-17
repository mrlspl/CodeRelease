/*
 * @file/Src/Modules/MoionControl/DortmundWalkingEngine/WalkPhases.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "WalkPhases.h"
#include "WalkTransitions.h"

float z = 0.02f;
Point p1(0, 0, 0, 0);
Point p2(0, 0, z, 0);

SingleSupportLeft::SingleSupportLeft(const Pose2f& requestedSpeed ,LegPoint& legPoint) :AbstractState("SingleSupportLeft") ,
    speed(requestedSpeed),
     _legPoint(legPoint),z(0.02f)

{
  transitions.push_back(new LeftStepFinish(*this));

}
void SingleSupportLeft::update()
{
//  std::cout << "I'm here man SingleSupportLeft" << std::endl;
  Point p3 = Point(speed.translation.x(),
      speed.translation.y(), z, 0);
  _legPoint = LegPoint(p1, p3);

  if (currentMovement.speed.translation.y() < 0)
    _legPoint.robotPose = p1;
  else
    _legPoint.robotPose = p3;

  counter ++;

}
void SingleSupportLeft::onEnter()
{
  counter = 0;
}
void SingleSupportLeft::onExit()
{
}

SingleSupportRight::SingleSupportRight(const Pose2f& requestedSpeed ,LegPoint& legPoint) :    AbstractState("SingleSupportRight"),
        speed(requestedSpeed),
 _legPoint(
        legPoint), z(0.02f)
{
  transitions.push_back(new RightStepFinish(*this));

}
void SingleSupportRight::update()
{
//  std::cout << "I'm here man SingleSupportRight" << std::endl;
  Point p3 = Point(speed.translation.x(),
      speed.translation.y(), z, 0);
  _legPoint = LegPoint(p3, p1);
  if (currentMovement.speed.translation.y() < 0)
  {

    Point p2 = Point(speed.translation.x(),
        speed.translation.y(), 0, 0);
    _legPoint.robotPose = p2;
  }
  else
  {
    Point p1 = Point(speed.translation.x(),
        speed.translation.y(), 0, 0);
    _legPoint.robotPose = p1;
  }

  counter ++;
}
void SingleSupportRight::onExit()
{
}
void SingleSupportRight::onEnter()
{
  counter = 0;
}


Ready::Ready(const Pose2f& requestedSpeed ,LegPoint& legPoint) :
        speed(requestedSpeed),
    AbstractState("Ready"), _legPoint(
        legPoint), stateCounter(0)
{
}

void Ready::update()
{
  _legPoint.robotPose = p1;
}
void Ready::onEnter()
{
  stateCounter = 1;
}
