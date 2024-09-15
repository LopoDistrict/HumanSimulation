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

namespace fs = std::filesystem;

void start_desire(const std::string& id) {
    Data obj;
    // Horrible function construction with: 2, if: 4, for: 2
    std::string gender = obj.get_value_char(id, 11); // Changed to get the character directly
    std::ifstream mailleFile("./data/temp/presence.asb");
    std::vector<std::string> maille;
    std::string line;

    // Read lines from the file into the mesh vector
    while (std::getline(mailleFile, line)) {
        maille.push_back(line);
    }
    obj.print_vector(maille);

    // Check if the id exists in maille
    
        for (int i = 0; i < maille.size(); ++i) {
            //std::cout << "-" << maille[i].substr(1, 7) << "-    " << std::endl;
            if (maille[i].substr(1, 7).find(id)){
                
                // Convert maille[i][j] (a char) to string
                std::string current_id(maille[i].substr(9, 8)); // Create a string from the character
                std::cout << "current_id" << current_id << std::endl;

                if (obj.get_value_char(current_id, 11) != gender) {
                    // Determine if idA starts desiring idB in its maille
                    std::vector<std::string> lpoint = obj.get_point_list(id);
                    std::vector<std::string> lc = obj.get_couple_list(id);
                    if (roll_random(120, 0, 200) && std::find(lpoint.begin(), lpoint.end(), current_id) == lpoint.end()
                    std::find(lc.begin(), lc.end(), current_id) == lc.end()) { // Simplified condition
                        std::cout << "desire started: " << id << std::endl;
                        std::cout << maille[i].substr(10, 8) << std::endl;
                        // Start a real attraction, so we remember the pointer
                        std::ofstream mem_file("./data/memory/couple.mem", std::ios::app);
                        // If the attraction worked, point idA to char idB (maille[i][j])
                        //Cellule(id, current_id); // Call Cellule with correct parameters
                        mem_file << id << ">" << current_id << "0"<< num_generator(2, 7) << std::endl;
                        obj.update_csv_cell(obj.get_index(id), 13, "yes"); //on change mtn il est en couple
                        //num_generator est le desir lorsqu'il est créer
                        //le desir varie selon certaine personne
                        //c'est pour cela qu'il ne peut pas être fixe
                        //ex: 0rbveqy0j0i>5ihdbpa0a4k25
                        //id pointe vers current_id
                        //id>current_id
                    }
                }
                
            }
        }
    
}

int main(){
    start_desire("4cdtwa69");
    return 0;
}

