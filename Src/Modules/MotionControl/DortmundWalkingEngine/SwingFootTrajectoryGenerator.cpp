/**
 * @author <a href="mailto:m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>.
 *
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

#include "SwingFootTrajectoryGenerator.hpp"
#include <iostream>
#include <fstream>


SwingFootTrajectoryGenerator::SwingFootTrajectoryGenerator(const LegPoint &legPoint) : _legPoint(legPoint) , deltaTime(0), numOfPolynomials(0)
{
  endSlope = Point(0.f, 0.f, 0.f);
  startSlope = Point(0.f, 0.f, 0.f);
}

void SwingFootTrajectoryGenerator::updateLegPoint()
{
  distanceOfSections.resize(7);
  Point zero = Point(0.f, 0.f, 0.f);
  interPolateInput.resize(2);         // First element for left foot and second for right.
  for (int i = 0; i < 2; i++)
  {
    interPolateInput.at(i).resize(7);   // Initialize for 5 control point;
  }

  distanceOfSections.at(0) = 0;
  distanceOfSections.at(1) = 1;
  distanceOfSections.at(2) = 5;
  distanceOfSections.at(3) = 12;
  distanceOfSections.at(4) = 16;
  distanceOfSections.at(5) = 22;
  distanceOfSections.at(6) = 23;


//  std::cout << " LegPoint = " << theStepDataOutPut.footStepsPoint.leftLeg.z << std::endl;
  interPolateInput.at(0).at(0) = zero;
  interPolateInput.at(0).at(1) = (0, 0, theStepDataOutPut.footStepsPoint.leftLeg.z / 8);
  interPolateInput.at(0).at(2) = (_legPoint.leftLeg.x / 4 ,_legPoint.leftLeg.y / 4, theStepDataOutPut.footStepsPoint.leftLeg.z / 4);
  interPolateInput.at(0).at(3) = (_legPoint.leftLeg.x  , _legPoint.leftLeg.y , theStepDataOutPut.footStepsPoint.leftLeg.z);
  interPolateInput.at(0).at(4) = (_legPoint.leftLeg.x * 4, _legPoint.leftLeg.y / 4, theStepDataOutPut.footStepsPoint.leftLeg.z / 4);
  interPolateInput.at(0).at(5) = (_legPoint.leftLeg.x / 8, _legPoint.leftLeg.y / 8, theStepDataOutPut.footStepsPoint.leftLeg.z / 8);
  interPolateInput.at(0).at(6) = zero;


  interPolateInput.at(1).at(0) = zero;
  interPolateInput.at(1).at(1) = (0, 0,theStepDataOutPut.footStepsPoint.rightLeg.z / 8);
  interPolateInput.at(1).at(2) = (_legPoint.rightLeg.x / 4 ,_legPoint.rightLeg.y / 4, theStepDataOutPut.footStepsPoint.rightLeg.z / 4);
  interPolateInput.at(1).at(3) = (_legPoint.rightLeg.x , _legPoint.rightLeg.y , theStepDataOutPut.footStepsPoint.rightLeg.z);
  interPolateInput.at(1).at(4) = (_legPoint.rightLeg.x / 4, _legPoint.rightLeg.y / 4, theStepDataOutPut.footStepsPoint.rightLeg.z / 4);
  interPolateInput.at(1).at(5) = (_legPoint.rightLeg.x / 8, _legPoint.rightLeg.y / 8, theStepDataOutPut.footStepsPoint.rightLeg.z / 8);
  interPolateInput.at(1).at(6) = zero;


}

void SwingFootTrajectoryGenerator::update(SwingLegTrajectoryOutput &swingLegTrajectoryOutput) {

  if (numOfPolynomials == 0)
  {
    updateLegPoint();
    leftPolynomialsCoeff = polynomial.calculateCoefficients(interPolateInput.at(0), startSlope, endSlope, distanceOfSections);
    rightPolynomialsCoeff = polynomial.calculateCoefficients(interPolateInput.at(0), startSlope, endSlope, distanceOfSections);
//    deltaTime = 0;
  }
  std::cout << "   binamose madar jende chandi   " << deltaTime << std::endl;

  swingLegTrajectoryOutput.swingLegTrajectory.leftLeg = polynomial.interpolate(leftPolynomialsCoeff, deltaTime, numOfPolynomials);
  swingLegTrajectoryOutput.swingLegTrajectory.rightLeg = polynomial.interpolate(rightPolynomialsCoeff, deltaTime, numOfPolynomials);
  std::ofstream log;
  log.open("/home/ali/salameManBeto.txt", std::ios::app);
  log << /*interpolateFrame << "," <<*/ swingLegTrajectoryOutput.swingLegTrajectory.leftLeg.z << "," << swingLegTrajectoryOutput.swingLegTrajectory.rightLeg.z<<"\n";
  log.close();
  deltaTime++;
  if (deltaTime >= distanceOfSections.at(numOfPolynomials + 1) - distanceOfSections.at(numOfPolynomials))
  {
    deltaTime = 0;
    numOfPolynomials++;
  }
  if(numOfPolynomials == 6)
    numOfPolynomials = 0;
}

MAKE_MODULE(SwingFootTrajectoryGenerator, dortmundWalkingEngine
)