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



void movement::update_csv_cell_modified(int row_index, int col_index, const std::string& new_value) {
        std::cout << "tool function definition: update_csv_cell" << std::endl;
        std::cout << row_index << std::endl;
        std::cout << col_index << std::endl;
        std::cout << new_value << std::endl;
        // Read the CSV file
        std::ifstream file("../data/TempChar.csv");
        std::vector<std::vector<std::string>> rows;
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            std::vector<std::string> row;

            while (std::getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            rows.push_back(row);
        }
        file.close();

        // Update the cell value
        rows[row_index][col_index] = new_value;        
        // Write the updated data back to the CSV file
        std::ofstream out_file("../data/TempChar.csv");
        for (const auto& row : rows) {
            for (size_t i = 0; i < row.size(); ++i) {
                out_file << row[i];
                if (i < row.size() - 1) {
                    out_file << ",";
                }
            }
            out_file << "\n";
        }
        out_file.close();
    }

std::string movement::get_simulation_param(int line) {
    std::cout << "Tool function definition: get_simulation_param" << std::endl;
    std::cout << line << std::endl;

    std::ifstream file("../data/temp/GenTempModule.asb");
    std::string result;
    if (file.is_open()) {
        for (int i = 0; i <= line; ++i) {
            std::getline(file, result);
        }
        file.close();
    } else {
        std::cerr << "Error opening file." << std::endl;
    }
    return result;
}

std::string movement::get_random_direction() {
    std::vector<std::string> main_dir = {"NN", "NE", "EE", "SE", "SS", "SO", "OO", "NO"};
    return main_dir[num_generator(0, main_dir.size() - 1)];
}

bool movement::out_of_border(int speed, int height, int width, int positionX, int positionY) {
    return (positionX + speed >= width || positionY + speed >= height ||
            positionX - speed < 0 || positionY - speed < 0);
}

std::string movement::get_majority_direction(const std::string& id, model& model_obj, Data& Data_obj) {

    std::unordered_map<std::string, int> dic_dir;

    std::vector<std::string> close_char = Data_obj.get_neighbour(id);
    int max = 0;

    for (const auto& character : close_char) {
        std::string direction = model_obj.get_value(character, 2);
        if (!direction.empty()) {
            dic_dir[direction] += 1;
        }
    }

    std::string major_dir;
    for (const auto& x : dic_dir) {
        if (x.second > max) {
            major_dir = x.first;
            max = x.second;
        }
    }
    return major_dir.empty() ? "null" : major_dir;
}

void movement::modify_model_mov(const std::string& id, const std::string& path, const std::string& value) {
    std::ifstream infile(path);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();

    if (lines.size() > 2) {
        lines[2] = value + "\n";
    }

    std::ofstream outfile(path);
    for (const auto& l : lines) {
        outfile << l << std::endl;
    }
    outfile.close();
}

void movement::single_char_movement(const std::string& id, model& model_obj, Data& Data_obj) {

    std::vector<std::string> close_char = Data_obj.get_neighbour(id);
    int height = std::stoi(get_simulation_param(0));
    int width = std::stoi(get_simulation_param(1));
    std::string climate = get_simulation_param(2);
    int mov = 0;
    int age = std::stoi(Data_obj.get_value_char(id, 1));
    std::string dir;

    if (age <= 35) {
        mov += num_generator(5, 40);
    } else if (age <= 65) {
        mov += num_generator(3, 25);
    } else {
        mov += num_generator(1, 13);
    }

    if (climate == "tropical") {
        mov -= num_generator(0, 2);
    } else if (climate == "arid") {
        mov -= num_generator(2, 4);
    } else if (climate == "continental") {
        mov -= num_generator(1, 3);
    }

    if (close_char.empty()) {
        if (model_obj.get_model(id, 3) == "mvt=null") {
            dir = get_random_direction();
        } else {
            dir = model_obj.get_value(id, 3);
        }
        mov += num_generator(3, 18);
    } else {
        movement movement;
        Data data;
        model model;
        dir = movement.get_majority_direction(id, model, data);
        if (dir == "null") {
            dir = get_random_direction();
        }
        mov += num_generator(1, 9);
    }

    while (!out_of_border(mov, height, width, std::stoi(Data_obj.get_position(id, 1)), std::stoi(Data_obj.get_position(id, 2)))) {
        dir = get_random_direction();
    }

    modify_model_mov(id, "../../data/memory/model" + id + ".dmem", "mvt=" + dir + std::to_string(mov));
    if (dir == "NN"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(mov + stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))));

    } else if (dir == "NE"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(mov + stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))));
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(mov + stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))));
    
    } else if (dir == "EE"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(mov + stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))));
    }
      else if (dir == "SE"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(-(mov + stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")))));
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(mov + stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))));
    }
      else if (dir == "SS"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(-(mov + stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")))));
    }
      else if (dir == "SO"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(-(mov + stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")))));
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(-(mov + stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")))));
    } 
      else if (dir == "OO"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(-(mov + stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")))));
    }
      else if (dir == "NO"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(mov + stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))));
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(-(mov + stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")))));
      }
}
