#ifndef MOVEMENT_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define MOVEMENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "../Data.h"
#include "rand.h"
#include "movement.h"
#include "reinforcement_intelligence/model.h"
#include "calculation.h"

    
    
void single_char_movement(const std::string& id);
std::string get_simulation_param(int line);    
std::string get_majority_direction(const std::string& id);
std::string get_random_direction();
bool out_of_border(int speed, int height, int width, int positionX, int positionY);
void modify_model_mov(const std::string& id, const std::string& path, const std::string& value, int l);
void update_csv_cell_modified(int row_index, int col_index, const std::string& new_value);


#endif //MOVEMENT_H