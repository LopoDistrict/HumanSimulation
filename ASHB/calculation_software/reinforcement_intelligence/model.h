#ifndef MODEL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define MODEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>


class model {
public:
    model(); 
    
    std::string get_model(const std::string& id, int line, std::string path2);
    std::string get_line_equivalent(const std::string& id, int line, std::string path2);
    std::string get_value(const std::string& id, int line, std::string path2);

};


#endif //MODEL_H