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
     _legPoint(legPoint),z(0.0141f)

{
  transitions.push_back(new LeftStepFinish(*this));

}
void SingleSupportLeft::update()
{
  Point p3 = Point(speed.translation.x(),
      speed.translation.y(), z, 0);
  _legPoint = LegPoint(p1, p3);

  _legPoint.newWalkingPhase = "SingleSupportLeft";

  counter++;
  _legPoint.stateCounter = counter;
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
        legPoint), z(0.0141f)
{
  transitions.push_back(new RightStepFinish(*this));

}
void SingleSupportRight::update()
{
  Point p3 = Point(speed.translation.x(),
      speed.translation.y(), z, 0);
  _legPoint = LegPoint(p3, p1);
  _legPoint.newWalkingPhase = "SingleSupportRight";

  counter++;
  _legPoint.stateCounter = counter;
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
        legPoint)
{
}

void Ready::update()
{
  counter++;
  _legPoint.stateCounter = counter;

  _legPoint.stateCounter = counter;
  _legPoint = LegPoint(p1,p1);
}
void Ready::onEnter()
{
  counter = 0;
}
