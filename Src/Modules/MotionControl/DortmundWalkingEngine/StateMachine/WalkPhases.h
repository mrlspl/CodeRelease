/*
 * @file/Src/Modules/MoionControl/DortmundWalkingEngine/WalkPhases.h
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#ifndef WALKPHASES_H_
#define WALKPHASES_H_

#include "Tools/StateMachine/AbstractState.h"
#include "../PatternGenerator2016.h"
#include "../FootStepsPoint.h"
#include "../LegPoint.h"
#include "../MovmentInformation.h"

class AbstractState;
class SingleSupportLeft: public AbstractState
{
public:
  SingleSupportLeft(const FootStepsPoint& footStepsPoint, LegPoint& legPoint);
  virtual void update();
  virtual void onEnter();
  virtual void onExit();
  FootStepsPoint _footStepsPoint;
  std::vector<LegPoint> legPointsFile;
private:
  LegPoint& _legPoint;
  std::vector<LegPoint> legPointsFileIter;
  Point p3 = Point(_footStepsPoint.footStepForward.x, 0, z, 0);
  float z;

};
class SingleSupportRight: public AbstractState
{
public:
  SingleSupportRight(const FootStepsPoint& footStepsPoint, LegPoint& legPoint);
  virtual void update();
  virtual void onEnter();
  virtual void onExit();

  std::vector<LegPoint> legPointsFile;
private:
  FootStepsPoint _footStepsPoint;
  LegPoint& _legPoint;
  float z;
  Point p3 = Point(_footStepsPoint.footStepForward.x, 0, z, 0);
};
class Ready: public AbstractState
{
public:
  Ready(const FootStepsPoint& footStepsPoint, LegPoint& legPoint);
  virtual void update();

    std::vector<LegPoint> legPointsFile;
private:
  FootStepsPoint _footStepsPoint;
    LegPoint& _legPoint;


};

class Recovery: public AbstractState
{
  Recovery(const FootStepsPoint& footStepsPoint, LegPoint& legPoint);
  ~Recovery();
  virtual void update();
  virtual void onEnter();
  virtual void onExit();

private:
  FootStepsPoint _footStepsPoint;
  LegPoint& _legPoint;
  Point p3 = Point(_footStepsPoint.footStepForward.x, 0, 0, 0);
  Point p4 = Point(_footStepsPoint.footStepForward.x,
      _footStepsPoint.footStepSide.y, 0, 0);
};

class KickRight: public AbstractState
{
  KickRight();
  ~KickRight();
  virtual void update();
  virtual void onEnter();
  virtual void onExit();
private:
  FootStepsPoint _footStepsPoint;
  LegPoint& _legPoint;
  Point p3 = Point(_footStepsPoint.footStepForward.x, 0, 0, 0);
  Point p4 = Point(_footStepsPoint.footStepForward.x,
      _footStepsPoint.footStepSide.y, 0, 0);
};

class KickLeft: public AbstractState
{
  KickLeft();
  ~KickLeft();
  virtual void update();
  virtual void onEnter();
  virtual void onExit();
private:
  FootStepsPoint _footStepsPoint;
  LegPoint& _legPoint;
  Point p3 = Point(_footStepsPoint.footStepForward.x, 0, 0, 0);
  Point p4 = Point(_footStepsPoint.footStepForward.x,
      _footStepsPoint.footStepSide.y, 0, 0);

};
#endif /* WALKPHASES_H_ */
