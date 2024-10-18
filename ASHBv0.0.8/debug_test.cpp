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
#include "calculation_software/rand.h"
#include "Data.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For std::find
#include <string>

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


int main(){
    Data Data_obj;
    Data_obj.eraseFileLine("./data/memory/model/test.txt", "2", 00);
    //std::cout << val << std::endl;
    return 0;
}

      //obj.update_csv_cell(obj.get_index(id), 13, "yes"); // Update CSV cell
             