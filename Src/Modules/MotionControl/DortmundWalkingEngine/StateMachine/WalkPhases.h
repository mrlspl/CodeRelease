/*
 * @file/Src/Modules/MoionControl/DortmundWalkingEngine/WalkPhases.h
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#ifndef WALKPHASES_H_
#define WALKPHASES_H_

#include "Tools/StateMachine/AbstractState.h"
#include "Tools/Math/Pose2f.h"
#include "../Point.h"
#include "../LegPoint.h"

class AbstractState;
class SingleSupportLeft: public AbstractState
{
public:
  SingleSupportLeft(const Pose2f& requestedSpeed ,LegPoint& legPoint);
  virtual void update();
  virtual void onEnter();
  virtual void onExit();
  void updateRobotPose();
  Point robotCurrentPosition;
  Point robotPoseAfterStep;
  float direction;
  unsigned int counter;

private:
  LegPoint& _legPoint;
  Pose2f speed;
  float z;

};
class SingleSupportRight: public AbstractState
{
public:
  SingleSupportRight(const Pose2f& requestedSpeed ,LegPoint& legPoint);
  virtual void update();
  virtual void onEnter();
  virtual void onExit();
  void updateRobotPose();
  Point robotCurrentPosition;
  Point robotPoseAfterStep;
  unsigned int counter;

private:
  LegPoint& _legPoint;
  Pose2f speed;
  float z;
};
class Ready: public AbstractState
{
public:
  Ready(const Pose2f& requestedSpeed ,LegPoint& legPoint);
  virtual void update();
  virtual void onEnter();
  unsigned int counter;

private:
    LegPoint& _legPoint;
    Pose2f speed;

};
//
//class Recovery: public AbstractState
//{
//  Recovery(const Pose2f& requestedSpeed ,LegPoint& legPoint);
//  ~Recovery();
//  virtual void update();
//  virtual void onEnter();
//  virtual void onExit();
//  unsigned int stateCounter;
//
//private:
//  LegPoint& _legPoint;
//};
//
//class KickRight: public AbstractState
//{
//  KickRight();
//  ~KickRight();
//  virtual void update();
//  virtual void onEnter();
//  virtual void onExit();
//  unsigned int stateCounter;
//private:
//  LegPoint& _legPoint;
//};
//
//class KickLeft: public AbstractState
//{
//  KickLeft();
//  ~KickLeft();
//  virtual void update();
//  virtual void onEnter();
//  virtual void onExit();
//private:
//  LegPoint& _legPoint;
//
//};
#endif /* WALKPHASES_H_ */
