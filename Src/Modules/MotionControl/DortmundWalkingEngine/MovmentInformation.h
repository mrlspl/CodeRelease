/*
 * MovmentInformation.h
 *
 *  Created on: Aug 2, 2018
 *      Author: ali
 */

#ifndef SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_MOVMENTINFORMATION_H_
#define SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_MOVMENTINFORMATION_H_
#include "Tools/Math/Pose2f.h"

class MovmentInformation
{

public:
  Pose2f speed;

  bool operator != (MovmentInformation other)
    {
    return speed != other.speed;
    }
};



#endif /* SRC_MODULES_MOTIONCONTROL_DORTMUNDWALKINGENGINE_MOVMENTINFORMATION_H_ */
