#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <tuple>    
#include "collision.h"
#include <unordered_set>
#include <algorithm>

/*
class collision {
public:
    int width;
    int height;
    std::vector<std::vector<std::vector<int>>> mesh;  // Corrected type
*/
collision::collision(){
    int width;
    int height;
    std::vector<std::vector<std::vector<int>>> mesh; 
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

    int collision::get_param(int line) {
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
            int heightSliced = round(height / 12.0);
            int widthSliced = round(width / 12.0);

            for (int i = 0; i < 12; i++) {
                int tempHeight = i * heightSliced;
                std::vector<std::vector<int>> row;
                for (int j = 0; j < 12; j++) {
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
/*
    bool collsion::CheckWord(char* filename, char* search){
    int offset; 
    std::string line;
    std::ifstream Myfile;
    Myfile.open (filename);

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            std::getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) 
            {
                std::cout << "found '" << search << "' in '" << line << "'" << std::endl;
                Myfile.close();
                return true;
            }
            else
            {
                std::cout << "Not found" << std::endl;
            }
        }
        Myfile.close();
    }
    else
        std::cout << "Unable to open this file." << std::endl;

    return false;
}*/

void collision::presence() {
    std::vector<std::string> presence;  // Store formatted presence strings for each mesh

    // Step 1: Read existing entries from the CSV file into a set
    std::unordered_set<std::string> existingEntries;
    std::ifstream csv_file("./data/presence.csv");
    std::string line;
    while (std::getline(csv_file, line)) {
        existingEntries.insert(line); // Assuming each line is a unique identifier
    }
    csv_file.close();

    // Step 2: Process the TempChar CSV file
    std::ifstream temp_csv_file("./data/TempChar.csv");
    std::getline(temp_csv_file, line); // Skip the header row

    for (const auto& row : mesh) {
        for (const auto& cell : row) {
            temp_csv_file.clear();
            temp_csv_file.seekg(0, std::ios::beg);
            std::getline(temp_csv_file, line); // Skip the header row
            
            std::string meshEntry = "";  // This will hold the IDs found in this mesh as "first_id second_id"
            
            while (std::getline(temp_csv_file, line)) {
                std::stringstream ss(line);
                std::string cellValue;
                std::vector<std::string> csvRow;
                while (std::getline(ss, cellValue, ',')) {
                    csvRow.push_back(cellValue);
                }

                // Check if the current entry is within the specified bounds
                if (std::stoi(csvRow[1]) >= cell[0] && std::stoi(csvRow[1]) <= cell[1] &&
                    std::stoi(csvRow[2]) >= cell[2] && std::stoi(csvRow[2]) <= cell[3]) {
                    
                    // Check if the entry already exists in the existingEntries set
                    if (existingEntries.find(csvRow[0]) == existingEntries.end()) {
                        // Append to meshEntry string
                        if (!meshEntry.empty()) {
                            meshEntry += " ";  // Add a space between IDs
                        }
                        meshEntry += csvRow[0];  // Add the new ID
                    }
                }
            }

            // If meshEntry contains any IDs, add it to presence
            if (!meshEntry.empty()) {
                presence.push_back(meshEntry);
            }
        }
    }

    temp_csv_file.close();

    // Write to the file only if we have new presence data
    if (!presence.empty()) {
        std::ofstream file_stream("./data/temp/presence.asb", std::ios::out | std::ios::app);
        if (file_stream.is_open()) {
            for (const auto& entry : presence) {
                file_stream << entry << "\n";  // Write each mesh's entries on a new line
            }
            file_stream.close();
        }
    }
}




/*
int main() {
    collision collision;
    collision.width =  collision.get_simulation_param(0);
    collision.height = collision.get_simulation_param(1);
    
    collision.separate();
    collision.presence();
    
    return 0;
}
*/