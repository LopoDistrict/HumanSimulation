#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <tuple>
#include "collision.h"

collision::collision() {  // Corrected constructor definition
    width = get_simulation_param(0);
    height = get_simulation_param(1);
    mesh.resize(height, std::vector<std::vector<int>>(width)); // Initialize mesh with dimensions
}

void collision::tempWrite(std::string file, const std::tuple<std::string, std::string, std::string, std::string>& values) {
    std::ofstream file_stream(file + ".asb", std::ios::out | std::ios::app);
    if (file_stream.is_open()) {
        file_stream << std::get<0>(values) << "," << std::get<1>(values) << "," << std::get<2>(values) << "," << std::get<3>(values) << "\n";
        file_stream.close();
    }
}
    void collision::tempWrite(std::string file, const std::vector<std::vector<std::string>>& presence) {
        std::ofstream file_stream(file + ".asb", std::ios::out | std::ios::app);
        if (file_stream.is_open()) {
            for (const auto& row : presence) {
                for (const auto& cell : row) {
                    file_stream << cell << " ";
                }
                file_stream << "\n";
            }
            file_stream.close();
        }
    }

    int collision::get_simulation_param(int line) {
        std::cout << "Tool function definition: get_simulation_param" << std::endl;
        std::cout << line << std::endl;

        std::ifstream file("./data/temp/GenTempModule.asb");
        std::string result;
        if (file.is_open()) {
            for (int i = 0; i <= line; ++i) {
                std::getline(file, result);
            }
            file.close();
        } else {
            std::cerr << "Error opening file." << std::endl;
        }
        std::cout << result << std::endl;
        return stoi(result);
    }


    void collision::separate() {
        const std::string fileObj = "./data/temp/tempSeparation.asb";
        std::ofstream flux(fileObj.c_str());
        if (flux) {
            int heightSliced = round(height / 15.0);
            int widthSliced = round(width / 15.0);

            for (int i = 0; i < 15; i++) {
                int tempHeight = i * heightSliced;
                std::vector<std::vector<int>> row;
                for (int j = 0; j < 15; j++) {
                    int tempWidth = j * widthSliced;
                    row.push_back({tempHeight, tempHeight + heightSliced, tempWidth, tempWidth + widthSliced});
                }
                mesh.push_back(row);
            }

            for (const auto& row : mesh) {
                for (const auto& cell : row) {
                    std::tuple<std::string, std::string, std::string, std::string> meshTuple;
                    meshTuple = std::make_tuple(std::to_string(cell[0]), std::to_string(cell[1]), std::to_string(cell[2]), std::to_string(cell[3]));
                    tempWrite("./data/temp/tempSeparation", meshTuple);
                }
            }
        } else {
            std::cout << "error opening the file" << std::endl;
        }
    }

    void collision::presence() {
        int num = 0; // Keeps track of the number of people in a mesh
        std::vector<std::vector<std::string>> presence;
        std::vector<std::string> tempChar;

        std::ifstream csv_file("./data/TempChar.csv");
        std::string line;
        std::getline(csv_file, line); // Skip the header row

        for (const auto& row : mesh) {
            for (const auto& cell : row) {
                csv_file.clear();
                csv_file.seekg(0, std::ios::beg);
                std::getline(csv_file, line); // Skip the header row
                while (std::getline(csv_file, line)) {
                    std::stringstream ss(line);
                    std::string cellValue;
                    std::vector<std::string> csvRow;
                    while (std::getline(ss, cellValue, ',')) {
                        csvRow.push_back(cellValue);
                    }
                    if (std::stoi(csvRow[1]) >= cell[0] && std::stoi(csvRow[1]) <= cell[1] && std::stoi(csvRow[2]) >= cell[2] && std::stoi(csvRow[2]) <= cell[3]) {
                        tempChar.push_back(csvRow[0]);
                        num++;
                    }
                }
                if (tempChar.size() > 1) {
                    presence.push_back(tempChar);
                }
                tempChar.clear();
                num = 0;
            }
        }

        csv_file.close();
        tempWrite("./data/temp/presence", presence);
    }

/*
int main() {
    collision collision;
    
    collision.separate();
    collision.presence();
    
    return 0;
}
*/