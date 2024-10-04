#ifndef DATA_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define DATA_H

#include <iostream>
#include <fstream>
#include "calculation_software/calculation.h"
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include "calculation_software/rand.h"
#include <algorithm>




class Data {
public:
    Data(); 
    void start_couple(const std::string& idA, const std::string& idB);
    std::string randmId();
    void start_desire(const std::string& id);
    void solitude(const std::string& id);
    int get_index(const std::string& id, std::string path = "./data/CharacterData.csv");
    std::string get_value_char(const std::string& id, int value_ind, std::string path = "./data/CharacterData.csv");
    std::vector<std::vector<float>> eval(const std::string& str);
    void bonheur(const std::string& id, float constant);
    bool age_update(const std::string& id, int day);
    void stress(const std::string& id, int constant);
    void health(const std::string& id, float constant);
    void print_vector(const std::vector<std::string>& vec);
    std::vector<std::string> get_neighbour(const std::string& id);
    std::string get_model(const std::string& id, int line);
    bool disease(const std::string& id);
    void mentalhealth(const std::string& id, float constant);
    void update_csv_cell(int row_index, int col_index, const std::string& new_value, std::string path = "./data/CharacterData.csv");
    void Hygiene(const std::string& id);
    std::string get_position(const std::string& id, int value_ind);
    bool procreation(const std::string& id, float const_breeding=0);
    std::string point(const std::string& id);
    void modify_desire(const std::string& idA, const std::string& idB, const std::string& constant);
    std::string get_desire_couple(const std::string& idA, const std::string& idB);
    std::string get_desire_single(const std::string& idA, const std::string& idB);
    void desire(const std::string& id, float constant, bool alr = false);
    std::vector<std::string> get_couple_list(const std::string& id);
    float Fbonheur(float c);
    void write_logs(const std::string& val);
    std::vector<std::string> get_point_list(const std::string&);
    std::string get_couple(const std::string& id);
    void eraseFileLine(std::string path, std::string eraseLine);
    void app_l(const std::string& file_path, int line_number, const std::string& value= "");
    float fastdiv(float quotient, const float& div);
    
};


#endif //DATA_H