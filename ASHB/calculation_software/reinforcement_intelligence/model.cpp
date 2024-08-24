#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include "model.h"
#include <algorithm>


    
    std::string model::get_model(const std::string& id, int line) {
        std::cout << "tool function definition: get_model" << std::endl;
        std::cout << id << std::endl;
        std::cout << line << std::endl;

        std::ifstream file("../../data/memory/model" + id + ".dmem");
        std::string result;
        if (file.is_open()) {
            for (int i = 0; i <= line; ++i) {
                std::getline(file, result);
            }
            file.close();
        }
        return result;
    }



    std::string model::get_line_equivalent(const std::string& id, int line){
        std::cout << "tool function definition: get_line_equivalent" << std::endl;
        std::cout << id << std::endl;
        std::cout << line << std::endl;

        std::string value;
        std::string lineFile = get_model(id, line);

        for (int i=0; i<lineFile.size(); i++){
            if(lineFile[i] == '='){
                std::cout << value << std::endl;
                return value;
            }
            value += lineFile[i];
        }
        return "Error: bad line or id";

    }

    std::string model::get_value(const std::string& id, int line){
        std::cout << "tool function definition: get_value" << std::endl;
        std::cout << id << std::endl;
        std::cout << line << std::endl;
        
        std::string value = (get_line_equivalent(id, line) + "=");
        std::string model = get_model(id, line);
        std::cout << model.erase(model.find(value), value.length()) << std::endl;
        return model.erase(model.find(value), value.length());
    }


