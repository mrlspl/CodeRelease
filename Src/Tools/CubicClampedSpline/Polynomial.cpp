#include "Polynomial.h"
#include <fstream>
#include <iostream>


Polynomial::Polynomial() {}

std::vector<std::vector<Point> > Polynomial::calculateCoefficients(std::vector<Point> pointInit, Point startPointSlope, Point endPointSlope, std::vector<float> timeInit) {

  int j = pointInit.size();
  int n = j - 1;
  alpha.resize(j);
  coefficients.resize(j);
  interval.resize(j);
  secondDer.resize(j);
  deltaTime.resize(n);
  interPolateRate.resize(n);
  for (int i = 0; i < j; i++) {
    coefficients.at(i).resize(4);
    coefficients.at(i).at(0) = pointInit.at(i);
  }
  for (int i = 0; i < n; i++)
  {
    deltaTime.at(i) = timeInit.at(i + 1) - timeInit.at(i);
  }

  alpha.at(0) = (((coefficients.at(1).at(0) - coefficients.at(0).at(0)) * 3.f) / deltaTime.at(0)) - (startPointSlope * 3.f);
  alpha.at(n) = (endPointSlope * 3.f) - ((coefficients.at(j - 1).at(0) - coefficients.at(j - 2).at(0)) * 3.f) / deltaTime.at(j - 2) ;

  for (int k = 1; k < n; k++)
  {
    alpha.at(k) = ((coefficients.at(k + 1).at(0) - coefficients.at(k).at(0))
                   * (3.f / deltaTime.at(k)))
                  -
             ((coefficients.at(k).at(0) - coefficients.at(k - 1).at(0)) * (3.f / deltaTime.at(k - 1)));
  }
  interval.at(0) = deltaTime.at(0) * 2.f;
  secondDer.at(0) = alpha.at(0) / interval.at(0);
  interPolateRate.at(0) = 0.5;

  for (int i = 1; i < n; i++)
  {
    interval.at(i) =  (interPolateRate.at(i - 1) * -deltaTime.at(i - 1)) + ((timeInit.at(i + 1) - timeInit.at(i - 1)) * 2);
    interPolateRate.at(i) =  Point(deltaTime.at(i), deltaTime.at(i), deltaTime.at(i)) / interval.at(i);
    secondDer.at(i) = (alpha.at(i) - (secondDer.at(i - 1) * deltaTime.at(i - 1))) / interval.at(i);
  }

  interval.at(n) = ((interPolateRate.at(n - 1) * -1) + 2.f ) * deltaTime.at(n - 1);

  secondDer.at(n) = (alpha.at(n) - (secondDer.at(n - 1) * deltaTime.at(n - 1))) / interval.at(n);

  coefficients.at(n).at(2) = secondDer.at(n);


//  coefficients.at(j-2).at(2) = endPointSlope;
  for (int y = n - 1; y >= 0 ; y--)
  {
    coefficients.at(y).at(2) = secondDer.at(y) - (interPolateRate.at(y) * coefficients.at(y + 1).at(2));
    coefficients.at(y).at(1) = ((coefficients.at(y + 1).at(0) - coefficients.at(y).at(0)) / deltaTime.at(y)) - ((coefficients.at(y+1).at(2) +  coefficients.at(y).at(2) * 2.f ) * deltaTime.at(y)) / 3.f;
    coefficients.at(y).at(3) = (coefficients.at(y + 1).at(2) - coefficients.at(y).at(2)) / (deltaTime.at(y) * 3.f);
  }


//  for (int i = 0; i < j; ++i)
//  {
//    std::cout << " coefficients.at(y).at(0)   "<< i<< "  " << coefficients.at(i).at(0).x<< "  " << coefficients.at(i).at(0).y<< "  " << coefficients.at(i).at(0).z << std::endl;
//    std::cout << " coefficients.at(y).at(1)   "<< i<< "  " << coefficients.at(i).at(1).x
//            << "  "
//            << coefficients.at(i).at(1).y
//            <<"  "
//            << coefficients.at(i).at(1).z
//            << std::endl;
//    std::cout << " coefficients.at(y).at(2)   "<< i<< "  " << coefficients.at(i).at(2).x << "  " << coefficients.at(i).at(2).y <<"  " << coefficients.at(i).at(2).z << std::endl;
//    std::cout << " coefficients.at(y).at(3)   "<< i<< "  " << coefficients.at(i).at(3).x << "  " << coefficients.at(i).at(3).y <<"  " << coefficients.at(i).at(3).z << std::endl;
//  }
  return coefficients;
}
Point Polynomial::interpolate(std::vector<std::vector<Point> > polynomialsCoefficients, float time ,int numOfPolynomials)
{

  return  (polynomialsCoefficients.at(numOfPolynomials).at(3) * std::pow(time, 3)
                          + polynomialsCoefficients.at(numOfPolynomials).at(2) * std::pow(time, 2)
                          + polynomialsCoefficients.at(numOfPolynomials).at(1) * time
                          + polynomialsCoefficients.at(numOfPolynomials).at(0));


}
void Polynomial::csvLogger(float interpolateFrame, float deltaPoint) {

  std::ofstream log;
  log.open("interpolatePoint.txt", std::ios::app);
  log << interpolateFrame << "," << deltaPoint<<"\n";
  log.close();

}