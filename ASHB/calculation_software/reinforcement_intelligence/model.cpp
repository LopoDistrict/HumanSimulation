#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include "model.h"
#include <algorithm>

    model::model(){
        
    }
    
#include <iostream>
#include <fstream>
#include <string>

std::string model::get_model(const std::string& id, int line, const std::string& path2) {
    std::cout << "Tool function definition: get_model" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Line number: " << line << std::endl;

    // Correctly concatenate the path
    std::string file_path = path2 + id + ".dmem";
    std::ifstream file(file_path);
    std::string result;

    if (file.is_open()) {
        for (int i = 0; i <= line; ++i) {
            std::getline(file, result);
            // Check if getline failed (e.g., the line doesn't exist)
            if (file.fail()) {
                std::cerr << "Error: Reached the end of the file or encountered an issue at line " << i << std::endl;
                return "Error: Invalid line number";
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Could not open file at " << file_path << std::endl;
        return "Error: Could not open file";
    }

    return result;
}


std::string model::get_line_equivalent(const std::string& id, int line,std::string path2) {
    std::cout << "tool function definition: get_line_equivalent" << std::endl;
    std::cout << id << std::endl;
    std::cout << line << std::endl;

    std::string lineFile = get_model(id, line, path2);
    std::string path = path + id + ".dmem";
    std::string value;
    for (char i : lineFile) {
        if (i == '=') {
            return value;
        }
        value += i;
    }
    return value;
}

std::string model::get_value(const std::string& id, int line, std::string path2) {
    std::cout << "tool function definition: get_value" << std::endl;
    std::cout << id << std::endl;
    std::cout << line << std::endl;

    std::string value = get_line_equivalent(id, line, path2);
    if (value.empty() || value == "Error: bad line or id") {
        std::cout << "Error: Invalid value returned from get_line_equivalent" << std::endl;
        return "Error: Invalid value"; // Handle invalid value case
    }

    std::string model = get_model(id, line, path2);
    if (model.empty()) {
        std::cout << "Error: Model is empty" << std::endl;
        return "Error: Model not found"; // Handle empty model case
    }

    size_t pos = model.find(value + "=");
    if (pos != std::string::npos) {
        return model.substr(pos + value.length() + 1); // Return the substring after the found value
    } else {
        std::cout << "Error: Value not found in model" << std::endl;
        return "Error: Value not found"; // Handle case where value is not found
    }
}

/*
int main(){
    model obj;
    std::string v;
    v = obj.get_model("0kfpdq75", 2);
    std::cout << "VALUE---" << v << std::endl;
    ////std::cout << "end model" << std::endl;
    //v = obj.get_line_equivalent("0kfpdq75", 2);
    //std::cout << "VALUE---" << v << std::endl;
    //////std::cout << "end line" << std::endl;
    //v = obj.get_value("0kfpdq75", 2);
    std::cout << "VALUE---" << v << std::endl;
    //std::cout << "end value" << std::endl;
}*/