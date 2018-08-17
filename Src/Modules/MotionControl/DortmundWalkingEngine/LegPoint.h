/*
 * @file/Src/Modules/MotionControl/DortMondWalkingEngine/LegPoint.h
 *
 * @author <A href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 */

#ifndef SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_LEGPOINT_H_
#define SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_LEGPOINT_H_

class LegPoint
{
public:
  LegPoint()
{}
  LegPoint(Point lf, Point rf) :
      leftLeg(lf), rightLeg(rf)
  {
  }
  LegPoint(Point lf, Point rf, Point rp) :
      leftLeg(lf), rightLeg(rf), robotPose(rp)
  {
  }
  Point leftLeg;
  Point rightLeg;
  Point robotPose;
//	bool isOnFloor[]; // First elment is left foot  {LeftFoot, RightFoot}

  LegPoint operator+= (const LegPoint& legpoint);
};

#endif /* SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_LEGPOINT_H_ */
