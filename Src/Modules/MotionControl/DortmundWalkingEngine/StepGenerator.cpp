/**
 /* @author <a href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>.
 /*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2018 MRL-SPL RoboCup Team
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

#include "StepGenerator.hpp"
#include <iostream>


StepGenerator::StepGenerator() : _legPoint(zero, zero, zero), zero(Point(0, 0 , 0, 0))
{
    stateMachine.addState("SingleSupportLeft",
                          new SingleSupportLeft(speed, _legPoint));
    stateMachine.addState("SingleSupportRight",
                          new SingleSupportRight(speed, _legPoint));
    stateMachine.addState("Ready", new Ready(speed, _legPoint));
  stateMachine.setState("SingleSupportLeft");
}

StepGenerator::~StepGenerator() {}

void StepGenerator::setSpeed() {

    speed = Pose2f(theMotionRequest.walkRequest.destination);
}

void StepGenerator::update(StepDataOutPut & stepDataOutPut) {

    setSpeed();
  stepDataOutPut.phaseSpeed = speed;
    stateMachine.update();

    stepDataOutPut.footStepsPoint.leftLeg = _legPoint.leftLeg;
//  std::cout << "left Leg point  x = " << stepDataOutPut.footStepsPoint.leftLeg.x
//            << "y = " << stepDataOutPut.footStepsPoint.leftLeg.y
//            << "z = " << stepDataOutPut.footStepsPoint.leftLeg.z << std::endl;
    stepDataOutPut.footStepsPoint.rightLeg = _legPoint.rightLeg;
//  std::cout << "right Leg point  x = " << stepDataOutPut.footStepsPoint.rightLeg.x
//            << "y = " << stepDataOutPut.footStepsPoint.rightLeg.y
//            << "z = " << stepDataOutPut.footStepsPoint.rightLeg.z << std::endl;

}

MAKE_MODULE(StepGenerator, dortmundWalkingEngine)