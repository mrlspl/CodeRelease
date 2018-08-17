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
#include "Representations/MotionControl/MotionRequest.h"

class LeftStepFinish : public AbstractTransition {
public:
  LeftStepFinish(const SingleSupportLeft& source);
  virtual bool condition();
  virtual std::string destination() const;
private:
  SingleSupportLeft const& source_;
//  SingleSupportLeft singleSupportLeft;
//  SingleSupportRight singleSupportRight;
};
class RightStepFinish : public AbstractTransition {
public:
  RightStepFinish(const SingleSupportRight& source);
  virtual bool condition();
  virtual std::string destination() const;
private:
  SingleSupportRight const& source_;
//  SingleSupportLeft singleSupportLeft;
//  SingleSupportRight singleSupportRight;
};
class StepPossible : public AbstractTransition {
public:
  StepPossible(const Pose2f& speed ,LegPoint& legPoint);
	virtual bool condition();
private:
LegPoint& _legPoint;
//SingleSupportLeft singleSupportLeft;
//SingleSupportRight singleSupportRight;
};
class IsReady : public AbstractTransition {
  virtual bool condition();
private:
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
