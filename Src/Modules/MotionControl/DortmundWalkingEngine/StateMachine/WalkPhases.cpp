/*
 * @file/Src/Modules/MoionControl/DortmundWalkingEngine/WalkPhases.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#include "WalkPhases.h"

float z = 0.02f;
Point p1(0, 0, 0, 0);
Point p2(0, 0, z, 0);

SingleSupportLeft::SingleSupportLeft(const FootStepsPoint& footStepsPoint,
    LegPoint& legPoint) :
     _footStepsPoint(footStepsPoint), _legPoint(
        legPoint), AbstractState("SingleSupportLeft"), z(0.02f)
{
  legPointsFile.clear();

}
void SingleSupportLeft::update()
{
  legPointsFile.push_back(LegPoint(p1, p3, p1));
}
void SingleSupportLeft::onEnter()
{
  legPointsFile.push_back(LegPoint(p1, p2, p1));
}
void SingleSupportLeft::onExit()
{
}

SingleSupportRight::SingleSupportRight(const FootStepsPoint& footStepsPoint,
    LegPoint& legPoint) :
    AbstractState("SingleSupportRight"), _footStepsPoint(footStepsPoint), _legPoint(
        legPoint), z(0.02f)
{
  legPointsFile.clear();
}
void SingleSupportRight::update()
{
  legPointsFile.push_back(LegPoint(p3, p1, p1));

}
void SingleSupportRight::onExit()
{
}
void SingleSupportRight::onEnter()
{
}


Ready::Ready(const FootStepsPoint& footStepsPoint, LegPoint& legPoint) :
    AbstractState("Ready"), _footStepsPoint(footStepsPoint), _legPoint(legPoint)
{
  legPointsFile.clear();
}

void Ready::update()
{

}
