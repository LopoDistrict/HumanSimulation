#ifndef RAND_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define RAND_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "include/BetterRand.h"

int num_generator(int num1, int num2);
bool roll_random(int tranche, int begin, int end);
float fl_gene();

#endif //RAND_H