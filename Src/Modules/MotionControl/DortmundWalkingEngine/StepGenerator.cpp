/*
 * @file/Src/Modules/MotionControl/DortMondWalkingEngine/StepGenerator.cpp
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */
#include "StepGenerator.h"
#include "StateMachine/WalkPhases.h"
#include <iostream>

#include "Tools/Debugging/CSVLogger.h"

StepGenerator::StepGenerator() :
    _legPoint(robotPose), currentWalkingPhase(numOfWalkingPhases), previewDelta(
        0), cyclePosCounter(0), curPreviewLength(0), direction(0), running(
        false), steps(), currentTimeStamp(0)

{
  stateMachine.addState("SingleSupportLeft",
      new SingleSupportLeft(speed, _legPoint));
  stateMachine.addState("SingleSupportRight",
      new SingleSupportRight(speed, _legPoint));
  stateMachine.addState("Ready", new Ready(speed, _legPoint));
  curPitch = targetPitch = 0;
  curStepDuration = 0.5;
  stateMachine.setState("SingleSupportLeft");
}

void StepGenerator::calcWalkSpeed()
{
  speed.translation = currentMovement.speed.translation * curStepDuration;

}
void StepGenerator::setPitch(float pitch)
{
  targetPitch = pitch;
}
float StepGenerator::getCurrentPitch()
{
  return curPitch;
}

int StepGenerator::getOptimalPreviewLength()
{
  unsigned int singleStepDurationInFrames = roundf(
      theWalkingEngineParams.footMovement.minStepDuration / 2)
      / theControllerParams.dt;
  return std::max((unsigned int) theControllerParams.N + 1,
      singleStepDurationInFrames + 1);
}

inline unsigned int StepGenerator::getPhaseLength(float ratio, float stepDur)
{
  float SingleStepDurationInFrames = (stepDur / 2) / theControllerParams.dt;
  return (int) roundf(ratio * SingleStepDurationInFrames);
}
StepGenerator::~StepGenerator()
{
}

void StepGenerator::keepPreviewSteps()
{
  do
  {
    stateMachine.update();
    footPointBuffer.push_front(_legPoint);
  } while (!footPointBuffer.full());

}
void StepGenerator::changeState()
{
  stateMachine.update();
}

void StepGenerator::initialWalkState()
{
  if (theMotionRequest.walkRequest.isReady)
    currentMovment.speed = Pose2f(0, 0, 0);
}

void StepGenerator::transitionToWalk(MovementInformation &moveInfo)
{
  newMovment = moveInfo;
  keepPreviewSteps();
}

void StepGenerator::update(FootSteps & steps)
{
  speed = thePatternGenRequest.speed;
//  std::cout << "speeeeeeeeeeeed " << speed.translation.x() << "          " << speed.translation.y() << std::endl;

  steps.reset();
//  acceptedDrawn[0] = false;
//  acceptedDrawn[1] = false;
//  acceptedDrawn[2] = false;

  calcWalkSpeed();

  addStep();
  keepPreviewSteps();
//  if (theFallDownState.state != FallDownState::upright)
//    reset();


    steps.reset();
  for (int i = 0; i < footPointBuffer.size(); i++)
  {
    footPosition.footPos[0] = footPointBuffer[i].leftLeg;
    footPosition.footPos[1] = footPointBuffer[i].rightLeg;

    footPosition.footPos[0].y += theWalkingEngineParams.footMovement.footYDistance;
    footPosition.footPos[1].y -= theWalkingEngineParams.footMovement.footYDistance;

    footPosition.singleSupportLen = getPhaseLength(
        1 - theWalkingEngineParams.footMovement.doubleSupportRatio,
        curStepDuration);

    steps.addStep(footPosition);
//    std::cout << " steps value = " << steps.getStep(i).footPos[0].x
//        << steps.getStep(i).footPos[0].y << steps.getStep(i).footPos[0].z
//        << "Foot steps  " << steps.getStep(i).footPos[1].x
//        << steps.getStep(i).footPos[1].y << steps.getStep(i).footPos[1].z
//        << std::endl;
  }

  this->steps = &steps;

  Point CoM(theRobotModel.centerOfMass.x() / 1000,
      theRobotModel.centerOfMass.y() / 1000,
      (theRobotModel.centerOfMass.z()) / 1000, 0);
  updateCoM(CoM);
  setPitch(thePatternGenRequest.pitch);

//  appliedReactiveStep[LEFT_FOOT] = 0;
//  appliedReactiveStep[RIGHT_FOOT] = 0;
  if (running)
  {
    for (int dim = 0; dim < 2; dim++)
    {
      Point mod = Point(theReferenceModificator[dim].x,
          theReferenceModificator[dim].y);
      for (int footNum = 0; footNum < 2; footNum++)
      {
        if (theReferenceModificator.aTime[dim].startFoot[footNum] != -1)
        {
//          sideStepSum[footNum] += mod;
//          appliedReactiveStep[footNum] += mod;
        }
      }
    }

  }

  steps.pitch = curPitch;
  steps.running = running;

  steps.time = currentTimeStamp;
  steps.cycleLength = (int) (curStepDuration * 100);
  if (running)
  {
    cyclePosCounter++;
    if (cyclePosCounter == steps.cycleLength) cyclePosCounter = 0;

    LOG("PatternGenerator2016_addStep", "currentWalkingPhase", currentWalkingPhase);
  }
  else
    cyclePosCounter = 0;
  steps.positionInCycle = cyclePosCounter;

  this->steps = NULL;

//  PLOT("module:PatternGenerator2016:PreviewLength", curPreviewLength);
//  if (!acceptedDrawn[0])
//    PLOT("module:PatternGenerator2016:AcceptedX", 0);
//  if (!acceptedDrawn[1])
//    PLOT("module:PatternGenerator2016:AcceptedY", 0);
//  if (!acceptedDrawn[2])
//    PLOT("module:PatternGenerator2016:AcceptedR", 0);

  steps.running = true;

//  std::cout << "steps.cycleLength" << steps.cycleLength << std::endl;
//  std::cout << "steps.emergencyStop" << steps.emergencyStop << std::endl;
//  std::cout << "steps.pitch" << steps.pitch << std::endl;
//  std::cout << "steps.positionInCycle" << steps.positionInCycle << std::endl;
//  std::cout << "steps.robotPoseAfterStep" << steps.robotPoseAfterStep.x  << std::endl;
//  std::cout << "steps.running" << steps.running << std::endl;
//  std::cout << "steps.suggestedStep.footPos[0]" << steps.suggestedStep.footPos[0].z << std::endl;
//  std::cout << "steps.suggestedStep.footPos[1]" << steps.suggestedStep.footPos[1].z << std::endl;
//  std::cout << "steps.time" << steps.time << std::endl;
//  std::cout << "steps.getStep(0).timestamp" << steps.getStep(0).timestamp << std::endl;
//  std::cout << "steps.cycleLength" << steps.cycleLength << std::endl;
//  std::cout << "steps.cycleLength" << steps.cycleLength << std::endl;

}

void StepGenerator::updateCoM(Point CoM)
{
  this->CoM = CoM;
}

void StepGenerator::reset()
{
  Point p(0, 0, 0, 0);
  stateMachine.setState("SingleSupportLeft");
  direction = 0;
  previewDelta = 0;
  running = false;
//  resetDelays();
  currentTimeStamp = 0;
  curPreviewLength = 0;
}
void StepGenerator::addStep()
{
//  PLOT("module:PatternGenerator2016:curStepDurationAddStep", curStepDuration);
  Footposition newStep;

//  std::cout << "what is fucking leftLeg value x =" << _legPoint.leftLeg.x << "    y = " << _legPoint.leftLeg.y<< "    z = " << _legPoint.leftLeg.z << std::endl;
  newStep.footPos[LEFT_FOOT] = _legPoint.leftLeg;
  newStep.footPos[RIGHT_FOOT] = _legPoint.rightLeg;

  newStep.footPos[LEFT_FOOT].y +=
      theWalkingEngineParams.footMovement.footYDistance;

//  std::cout << "theWalkingEngineParams.footMovement.footYDistance: " << theWalkingEngineParams.footMovement.footYDistance << std::endl;

//  std::cout << "new Steps      "  <<  newStep.footPos[RIGHT_FOOT].z;
  newStep.footPos[RIGHT_FOOT].y +=
      -theWalkingEngineParams.footMovement.footYDistance;

//  newStep.footPos[LEFT_FOOT].rotate2D(robotPose.robotPose.r + footModifier[currentWalkingPhase][LEFT_FOOT].r);
//  newStep.footPos[RIGHT_FOOT].rotate2D(robotPose.robotPose.r + footModifier[currentWalkingPhase][RIGHT_FOOT].r);

  if (currentWalkingPhase==firstSingleSupport || currentWalkingPhase==secondSingleSupport)
    newStep.frameInPhase=newStep.singleSupportLen;

  for (int i = 0; i < 2; i++)
  {
    ASSERT(newStep.footPos[i] == newStep.footPos[i]);

    // This makes boom if a foot on the floor is repositioned by more than 1 mm
    // Check transitions from phase to phase including rotation, also custom
    // steps. Same for rotation.
    {
      // TODO: fix this crash
      //ASSERT(!(lastStep.onFloor[i] && newStep.onFloor[i]) || (lastStep.footPos[i].euklidDistance3D(newStep.footPos[i]-appliedReactiveStep[i]) < 0.001 && fabs(lastStep.footPos[i].r - newStep.footPos[i].r) < 0.01));
    }

  }

//  std::cout  << "currentState StepGenerator        " << stateMachine.getCurrentStateId() << std::endl;
  if (stateMachine.getCurrentStateId() == "SingleSupportLeft")
  {
    std::cout << "into first if" << std::endl;
    newStep.phase = WalkingPhase::firstSingleSupport;
    std::cout << "newStep.phase  " << newStep.phase << std::endl;

  }
  else if (stateMachine.getCurrentStateId() == "SingleSupportRight")
  {
    std::cout << "into second if" << std::endl;
    newStep.phase = WalkingPhase::secondSingleSupport;
    std::cout << "newStep.phase   " << newStep.phase << std::endl;
  }


  newStep.singleSupportLen = getPhaseLength(
      1 - theWalkingEngineParams.footMovement.doubleSupportRatio,
      curStepDuration);
  newStep.doubleSupportLen = getPhaseLength(
      1 - theWalkingEngineParams.footMovement.doubleSupportRatio,
      curStepDuration);
  newStep.frameInPhase = 0;

  newStep.direction = direction;
  newStep.phase = currentWalkingPhase;
  newStep.singleSupportLen = getPhaseLength(
      1 - theWalkingEngineParams.footMovement.doubleSupportRatio,
      curStepDuration);
  newStep.frameInPhase = 0;
  newStep.timestamp = currentTimeStamp; // time is the frame number when it is executed after preview
  currentTimeStamp++;
  ASSERT(
      newStep.frameInPhase < newStep.doubleSupportLen
          || newStep.frameInPhase < newStep.singleSupportLen);

  newStep.speed = currentMovement.speed;
  // Add to buffer for ZMP/IP-Controller (sent via FootSteps)
}

MAKE_MODULE(StepGenerator, dortmundWalkingEngine)

