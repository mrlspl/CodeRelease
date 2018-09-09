/**
 * author <a href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>.
 *
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2015 MRL-SPL RoboCup Team
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 *
  */

#include "LegPoint.h"

LegPoint &LegPoint::operator=(const LegPoint &lp)
{
  leftLeg.x = lp.leftLeg.x;
  leftLeg.y = lp.leftLeg.y;
  leftLeg.z = lp.leftLeg.z;

  rightLeg.x = lp.rightLeg.x;
  rightLeg.y = lp.rightLeg.y;
  rightLeg.z = lp.rightLeg.z;

  robotPose.x = lp.robotPose.x;
  robotPose.y = lp.robotPose.y;
  robotPose.z = lp.robotPose.z;

  return *this;

}