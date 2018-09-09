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

#ifndef CODERELEASE_SWINGFOOTTRAJECTORYGENERATOR_HPP
#define CODERELEASE_SWINGFOOTTRAJECTORYGENERATOR_HPP

#include "Tools/Module/Module.h"
#include "Point.h"
#include "Representations/MotionControl/SwingLegTrajectoryOutput.hpp"
#include "../../../Modules/MotionControl/DortmundWalkingEngine/LegPoint.h"
#include "../../../Tools/CubicClampedSpline/Polynomial.h"
#include "Representations/MotionControl/StepDataOutPut.hpp"
#include <math.h>


MODULE(SwingFootTrajectoryGenerator,
{,
    REQUIRES(StepDataOutPut),
    PROVIDES(SwingLegTrajectoryOutput),
});
class SwingFootTrajectoryGenerator : public SwingFootTrajectoryGeneratorBase
{
public:
  SwingFootTrajectoryGenerator(){}
  SwingFootTrajectoryGenerator(const LegPoint &legPoint);

private:

  void update(SwingLegTrajectoryOutput &swingLegTrajectoryOutput);

  void updateLegPoint();

  Polynomial polynomial;

  std::vector<std::vector<Point> > leftPolynomialsCoeff;
  std::vector<std::vector<Point> > rightPolynomialsCoeff;
  std::vector<std::vector<Point> > interPolateInput;


  LegPoint _legPoint;

  int deltaTime;

  int numOfPolynomials = 0;

  std::vector<float> distanceOfSections;

  Point startSlope, endSlope;
};


#endif //CODERELEASE_SWINGFOOTTRAJECTORYGENERATOR_HPP
