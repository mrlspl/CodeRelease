/*
 * Polynomial.h
 * @author <a href="mailto: m.hassanpour@mrl-spl.ir">Mostafa Hassanpour</a>
 *
 */
#include <vector>
#include <cmath>
#include <list>
#include "../../Modules/MotionControl/DortmundWalkingEngine/Point.h"


class Polynomial
{
private:

    std::vector<float> deltaTime;
    std::vector<Point> alpha;
    std::vector<Point> interval;
    std::vector<Point> interPolateRate;
    std::vector<Point> secondDer;

public:

std::vector<std::vector<Point> > coefficients;  // f(x) = a*x^3 + b * x^2 + c * x + d

Polynomial();

  std::vector<std::vector<Point> > calculateCoefficients(std::vector<Point> pointInit, Point startPointSlope, Point endPointSlope, std::vector<float> timeInit);

Point interpolate(std::vector<std::vector<Point> > polynomialsCoefficients, float time ,int numOfPolynomials);




  void csvLogger(float interpolateFrame, float deltaPoint);
};

