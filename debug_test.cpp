#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <tuple>    
//#include "../collision.h"
#include <filesystem>
#include <iostream>
//#include "calculation_software/rand.h"
//#include "Data.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For std::find
#include <string>
#include <unordered_map>
#include "calculation_software/reinforcement_intelligence/model.h"

/*

void start_desire(const std::string& id) {
    Data obj; // Assuming Data is a defined class
    std::string gender = obj.get_value_char(id, 11); // Get the character directly
    
    std::ifstream mailleFile("./data/temp/presence.asb");
    std::vector<std::string> maille;
    std::string line;

    // Read lines from the file into the maille vector
    while (std::getline(mailleFile, line)) {
        maille.push_back(line);
    }
    obj.print_vector(maille); // Assuming print_vector is a defined method

    // Check if the id exists in maille
    for (int i = 0; i < maille.size(); ++i) {
        if (maille[i].substr(1, 7).find(id)) {
            // Convert maille[i][j] (a char) to string
            std::string current_id(maille[i].substr(9, 8)); // Create a string from the character
            std::cout << "current_id: " << current_id << std::endl;

            if (obj.get_value_char(current_id, 11) != gender) {
                // Determine if idA starts desiring idB in its maille
                std::vector<std::string> lpoint = obj.get_point_list(id);
                std::vector<std::string> lc = obj.get_couple_list(id);

                if (roll_random(120, 0, 200) && 
                    (std::find(lpoint.begin(), lpoint.end(), current_id) == lpoint.end()) &&
                    (std::find(lc.begin(), lc.end(), current_id) == lc.end())) {    
                    
                    std::cout << "Desire started: " << id << std::endl;
                    std::cout << maille[i].substr(10, 8) << std::endl;

                    // Start a real attraction, so we remember the pointer
                    std::ofstream mem_file("./data/memory/couple.mem", std::ios::app);
                    mem_file << id << ">" << current_id << "0" << num_generator(2, 7) << std::endl;
                 }
            }
        }
    }
}    */
void modify_model_mov(const std::string& id, const std::string& path, const std::string& value, int l) {
    std::cout << "Tool function: modify_model_mov" << std::endl;
    

    std::ifstream file(path);
    std::vector<std::string> lines;
    std::string line;

    // Read all lines from the file
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Check if the line index is valid
    if (l < 0 || l >= lines.size()) {
        std::cerr << "Error: Line index " << l << " is out of range." << std::endl;
        return;
    }
    // Overwrite the specified line with the new value
    lines[l] = value;
    std::ofstream filew(path);
    for (size_t i = 0; i < lines.size(); ++i) {
        filew << lines[i];
        if (i < lines.size() - 1) {
            filew << std::endl; // Add newline for all lines except the last one
        }
    }
    filew.close();
}

std::unordered_map<std::string, std::string> modval_to_umap(const std::string& id, int line){
    //va chercher val dans model pour le place dans un umap
    model mod_obj;
    std::string mod_value = mod_obj.get_value(id, line, "./data/memory/model/"+id+".dmem");
    std::unordered_map<std::string, std::string> umap;
    std::vector<std::string> temp_split;
    std::string item;
    std::stringstream ss(mod_value);

    while(std::getline(ss, item, ',')){
        temp_split.push_back(item);
    }

    for(int i=1; i<temp_split.size(); i+=2){
        umap.insert(std::make_pair(temp_split[i-1], temp_split[i]));
    }
    //loop en prenant les val 2 par 2, puis associer dans umap
    return umap;
}

void w_unmap_model(const std::string& id, std::unordered_map<std::string, std::string> umap, int l){
    //write umap to model_file
    model mod_obj;
    std::string conv = mod_obj.get_line_equivalent(id, l, "./data/memory/model/"+id+".dmem") + "=";

    for(const auto& x: umap){
        conv += x.first + "," + x.second + ",";
    }
    //conv += "}";
    modify_model_mov(id, "./data/memory/model/"+ id + ".dmem", conv, 1);
}

int main(){
    std::unordered_map<std::string, std::string> umap = {{"a", "1"}, {"b", "2"}};
    w_unmap_model("l", umap, 1);
    std::cout << "done writting" << std::endl;
    std::unordered_map<std::string, std::string> umap2 = modval_to_umap("l", 1);
    std::cout << "showing umap" << std::endl;
    for (const auto& x : umap2){
        std::cout << x.first << " " << x.second << std::endl;
    }

    return 0;
}

      //obj.update_csv_cell(obj.get_index(id), 13, "yes"); // Update CSV cell
             