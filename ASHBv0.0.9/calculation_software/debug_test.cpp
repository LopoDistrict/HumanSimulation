#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <tuple>    
#include "../collision.h"


int main(){
    collision collision;
    collision.width =  collision.get_simulation_param(0);
    collision.height = collision.get_simulation_param(1);
    
    collision.separate();
    collision.presence();
    return 0;
}