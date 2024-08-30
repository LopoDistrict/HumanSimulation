#ifndef CALCULATION_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CALCULATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>


float Fbonheur(float c);
float Fsolitude(float PreSolitudeStats, float NewValues);
float Fdesire(float d, int c);

#endif //CALCULATION_H
