#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <unordered_set>
#include <tuple>
#include <algorithm>

class collision {
public:
    int width;
    int height;
    std::vector<std::vector<std::vector<int>>> mesh;  // Corrected type
    bool isMeshInitialized = false;
    
    collision(); // Constructor
    void tempWrite(std::string file, const std::tuple<std::string, std::string, std::string, std::string>& values);
    void tempWrite(std::string file, const std::vector<std::vector<std::string>>& presence);
    std::string get_param(int line);
    //bool CheckWord(char* filename, char* search);
    void separate();
    void presence();
    void loadMeshFromFile();

};

#endif // COLLISION_H