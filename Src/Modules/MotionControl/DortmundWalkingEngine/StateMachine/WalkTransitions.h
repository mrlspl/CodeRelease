/*
 * @file/Modules/MotionControl/DortmundWalkingEngine/StateMachine/Transitions.h
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */


#ifndef TRANSITIONS_H_
#define TRANSITIONS_H_
#include "WalkPhases.h"
#include "../LegPoint.h"
#include "Representations/Sensing/FallDownState.h"
#include "../FootStepsPoint.h"
#include "Representations/MotionControl/MotionRequest.h"


class StepFinish : public AbstractTransition {
public:
  StepFinish(const FootStepsPoint& footStepsPoint, LegPoint& legPoint);
	virtual bool condition();
private:
	LegPoint& _legPoint;
	FootStepsPoint _footStepsPoint;
  Point p4 = Point(_footStepsPoint.footStepForward.x ,_footStepsPoint.footStepSide.y, 0, 0);
//  SingleSupportLeft singleSupportLeft;
//  SingleSupportRight singleSupportRight;
};
class StepPossible : public AbstractTransition {
public:
  StepPossible(const FootStepsPoint& footStepsPoint,  LegPoint& legPoint);
	virtual bool condition();
private:
LegPoint& _legPoint;
FootStepsPoint _footStepsPoint;
MotionRequest motionRequest;
//SingleSupportLeft singleSupportLeft;
//SingleSupportRight singleSupportRight;
};
class IsReady : public AbstractTransition {
  virtual bool condition();
private:
  MotionRequest motionRequest;
//  SingleSupportLeft singleSupportLeft;
//  SingleSupportRight singleSupportRight;
};





class KickRequestRight : public AbstractTransition {
public:
	virtual bool condition();
};
class KickRequestLeft : public AbstractTransition {
  virtual bool condition();
};
class KickFinish : public AbstractTransition {
  virtual bool condition();
};
class RobotIsFalling : public AbstractTransition {
  virtual bool condition();
};
class RobotRecoverd : public AbstractTransition {
  virtual bool condition();
};


#endif /* TRANSITIONS_H_ */
