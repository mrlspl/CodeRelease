/*
 * @file/Src/Modules/MotionControl/DortMondWalkingEngine/StepGenerator.h
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */
#ifndef SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_STEPGENERATOR_H_
#define SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_STEPGENERATOR_H_
#include "StepData.h"

#include "Parameters.h"
#include "Point.h"
#include "WalkingInformations.h"
#include "Representations/MotionControl/SpeedInfo.h"
#include "Representations/MotionControl/WalkingEngineParams.h"
#include "Representations/MotionControl/PatternGenRequest.h"
#include "Representations/MotionControl/WalkingInfo.h"
#include "Representations/Sensing/RobotModel.h"
#include "Representations/MotionControl/FootSteps.h"
#include "Representations/Configuration/RobotDimensions.h"
#include "Representations/Sensing/FallDownState.h"
#include "Representations/MotionControl/ControllerParams.h"
#include "Representations/MotionControl/MotionRequest.h"
#include "Representations/MotionControl/ReferenceModificator.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Tools/RingBufferWithSum.h"
#include "Representations/MotionControl/ControllerParams.h"
#include "Representations/Modeling/BallModel.h"
#include "Tools/Module/Module.h"
#include "Tools/StateMachine/StateMachine.h"
#include "Tools/RingBuffer.h"
#include "StateMachine/WalkPhases.h"
#include "StateMachine/WalkTransitions.h"
MODULE(StepGenerator,
{ ,
  REQUIRES(WalkingEngineParams),
  REQUIRES(PatternGenRequest),
  REQUIRES(RobotModel),
  REQUIRES(RobotDimensions),
  REQUIRES(FallDownState),
  REQUIRES(ControllerParams),
  REQUIRES(MotionRequest),
  USES(WalkingInfo),
  USES(ReferenceModificator),
  REQUIRES(FrameInfo),
  REQUIRES(BallModel),
  REQUIRES(BallModelAfterPreview),
  PROVIDES(FootSteps),
//  PROVIDES(SpeedInfo),
});

class StepGenerator : public StepGeneratorBase
{
public:
  StepGenerator();
  virtual ~StepGenerator();

  LegPoint robotPose;


private:
  StateMachine stateMachine;
  LegPoint _legPoint;
  MovementInformation currentMovment;


  MovementInformation newMovment;


  FootSteps *steps;
  Pose2f speed;



  float targetPitch;
  float curPitch;
  float curStepDuration;

  float direction;

  int previewDelta;

  bool running;

  int currentTimeStamp;
  int curPreviewLength;



  Point CoM;


  RingBuffer<LegPoint, 50> footPointBuffer;
  Footposition footPosition;

  WalkingPhase currentWalkingPhase;

  MovementInformation currentMovement;


  int cyclePosCounter;

  Point stepRobotPose;



void setPitch(float pitch);
float getCurrentPitch();
int getOptimalPreviewLength();

inline unsigned int getPhaseLength(float ratio,float stepDur);

void keepPreviewSteps();
void changeState();

void initialWalkState();
void transitionToWalk(MovementInformation &moveInf);
void updateRobotPose();
void updateCounter();

void update(FootSteps & footSteps);
void updateCoM(Point CoM);

void reset();

void handlePreviewDelta(int max);

void addStep();

void calcWalkSpeed();
void addFootSteps();

};


#endif /* SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_STEPGENERATOR_H_ */
