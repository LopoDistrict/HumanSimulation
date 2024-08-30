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

//check Data.cpp en tête

//bug: lors de deplacement negatif Ouest sud etc
//tout la coordonnées devient négatives alors que mov la variable
//devrait simplement soustraitre la valeur deja presente mais bug 
//force 2:27


//vu  qu'il y a un probleme apparement avec la compilation et l'exec de clock avec 
//movement on va compiler clock en dehors de movement et appeler movement (qui lui marche de son
//dossier avec un param: l'id)


void update_csv_cell_modified(int row_index, int col_index, const std::string& new_value) {
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

std::string get_simulation_param(int line, std::string path) {
    std::cout << "Tool function definition: get_simulation_param" << std::endl;
    std::cout << line << std::endl;

    std::ifstream file(path);
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
    return result;
}

std::string get_random_direction() {
    std::vector<std::string> main_dir = {"NN", "NE", "EE", "SE", "SS", "SO", "OO", "NO"};
    std::cout << main_dir[num_generator(0, main_dir.size() - 1)] << std::endl;
    return main_dir[num_generator(0, main_dir.size() - 1)];
}


bool out_of_border(int speed, int height, int width, int positionX, int positionY, const std::string& dir) {
    std::cout << "tool function: out_of_border" << std::endl;
    
    // Direction map for determining x and y multipliers
    std::unordered_map<std::string, std::string> dir_map{
        {"NN", "++"}, {"NE", "++"}, {"EE", "++"},
        {"SE", "+-"}, {"SS", "+-"}, {"SO", "--"},
        {"OO", "-+"}, {"NO", "-+"}
    };

    // Check if the direction exists in the map
    if (dir_map.find(dir) == dir_map.end()) {
        std::cerr << "Error: Invalid direction provided" << std::endl;
        return true; // If invalid direction, assume out of bounds
    }

    std::string dir_value = dir_map[dir];

    // Extract and convert the direction multipliers
    int x_factor = (dir_value[0] == '+') ? 1 : -1;
    int y_factor = (dir_value[1] == '+') ? 1 : -1;

    std::cout << "x_factor: " << x_factor << std::endl;
    std::cout << "y_factor: " << y_factor << std::endl;

    // Check if the new position after moving would be out of borders
    int new_positionX = positionX + (speed * x_factor);
    int new_positionY = positionY + (speed * y_factor);

    std::cout << "New X: " << new_positionX << " (width: " << width << ")" << std::endl;
    std::cout << "New Y: " << new_positionY << " (height: " << height << ")" << std::endl;

    bool is_out_of_border = (new_positionX >= width || new_positionY >= height ||
                             new_positionX <= 0 || new_positionY <= 0);

    if (is_out_of_border) {
        std::cout << "Out of border: true" << std::endl;
    } else {
        std::cout << "Out of border: false" << std::endl;
    }

    return is_out_of_border;
}



std::string get_majority_direction(const std::string& id) {
    model model_obj;
    Data Data_obj;
    std::cout << "tool function: get_majority_direction" << std::endl;
    std::unordered_map<std::string, int> dic_dir;


    std::vector<std::string> close_char = Data_obj.get_neighbour(id);
    int max = 0;

    for (const auto& character : close_char) {
        std::string direction = model_obj.get_value(character, 2, "../data/memory/model/");
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
    std::string l = major_dir.empty() ? "null" : major_dir;
    std::cout << l << std::endl;
    return major_dir.empty() ? "null" : major_dir;
}

void modify_model_mov(const std::string& id, const std::string& path, const std::string& value, int l) {
    std::cout << "tool function: modify_model_mov" << std::endl;
    std::cout << path << std::endl;
    std::ifstream file(path);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    lines[l] = value;

    std::ofstream filew(path);
    for (const auto& line : lines) {
        filew << line << std::endl;
    }
    filew.close();
}

void single_char_movement(const std::string& id) {
    model model_obj;
    Data Data_obj;
    std::vector<std::string> close_char = Data_obj.get_neighbour(id);
    int height = std::stoi(get_simulation_param(0));
    int width = std::stoi(get_simulation_param(1));
    std::string climate = get_simulation_param(2);
    int mov = 0;
    int age = std::stoi(Data_obj.get_value_char(id, 1, "../data/CharacterData.csv"));
    std::string dir = "";

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

    std::cout << "error -3" << std::endl;
    if (close_char.empty()) {
        std::cout << "error -3: nobody" << std::endl;
        if (model_obj.get_model(id, 2,  "../data/memory/model/") == "mvt=null") {
            std::cout << "dir-2: " << dir << std::endl;
            dir = get_random_direction();
            std::cout << "error -3: == mvt=null" << std::endl;
        } else {
            std::cout << "error -3 != mvt == null" << std::endl;
            std::cout << "dir-1: " << dir << std::endl;            

            dir = model_obj.get_value(id, 2,  "../data/memory/model/").substr(0, 2);
            //on substr == slice car sinon on reprend toute la vitesse et la concatene
            //ici on pveut juste la dir
            std::cout << "dir0" << dir << std::endl;
            std::cout << "error -3 ap get_value(id, 2)" << std::endl;
        }
        std::cout << "error -3 av" << std::endl;
        mov += num_generator(3, 18);
        std::cout << "error -3 ap" << std::endl;
    std::cout << "error -2" << std::endl;
    } else {
        std::cout << "dir1: " << dir << std::endl;        
        dir = get_majority_direction(id);
        std::cout << "dir2: " << dir << std::endl;
        if (dir == "null") {
            std::cout << "dir3: " << dir << std::endl;
            dir = get_random_direction();
            std::cout << "dir4: " << dir << std::endl;
        }
        mov += num_generator(1, 9);
    }
    std::cout << "error -1" << std::endl;


    while (out_of_border(mov, height, width, 
                    std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")), 
                    std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")), 
                    dir)) {
        dir = get_random_direction();
        std::cout << "oob" << std::endl;

        //si l'entité et proche d'une bordure on lui donneun direction autre aléatoir
        //doit changer ce passage prendre en compte que la direction doit 
        //totalement etre oposé de plus peut prendre en compte dans 
        //la fonction out_of_border les diff directions
        //! peut donc associer les directios avec un x et y qui peut etre nul
        //afin de nous éviter tout les lignes en dessous (ou pas)
        //voir la feuille sur les mouvements!!
    }

    std::cout << "no error 0" << std::endl;
    std::string value = "mvt=" + dir + std::to_string(mov);
    std::cout << "value: " << value << std::endl;
    modify_model_mov(id, "../data/memory/model/" + id + ".dmem", value, 2);
    std::cout << "no error 1" << std::endl;
    std::cout << "dir: " << dir << std::endl;
    std::cout << "mov: " << mov << std::endl;
    if (dir == "NN"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(mov + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))),"../data/TempChar.csv");
    //std::cout << "no error 2" << std::endl;,"../data/TempChar.csv"
    } else if (dir == "NE"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(mov + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))),"../data/TempChar.csv");
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(mov + std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))),"../data/TempChar.csv");
    //std::cout << "no error 3" << std::endl;
    } else if (dir == "EE"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(mov + std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))),"../data/TempChar.csv");
    }
    //std::cout << "no error 4" << std::endl;
      else if (dir == "SE"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string((-mov + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")))),"../data/TempChar.csv");
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(mov +   std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))),"../data/TempChar.csv");
    }
    //std::cout << "no error 5" << std::endl;
      else if (dir == "SS"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string((-mov + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")))),"../data/TempChar.csv");
    }
    //std::cout << "no error 6" << std::endl;
      else if (dir == "SO"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string((-mov + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")))),"../data/TempChar.csv");
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string((-mov + std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")))),"../data/TempChar.csv");
    } 
    //std::cout << "no error 7" << std::endl;
    else if (dir == "OO"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string((-mov + std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")))),"../data/TempChar.csv");
    }
    //std::cout << "no error 8" << std::endl;
      else if (dir == "NO"){
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(mov + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))),"../data/TempChar.csv");
        Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string((-mov + std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv")))),"../data/TempChar.csv");
    }
}

/*
int main(){
    std::string id =  "9tgyip24";
    single_char_movement(id);
    //get_simulation_param(0) ;
    //get_simulation_param(1) ;
    //get_simulation_param(2) ;
    //get_majority_direction(id) ;
    //get_random_direction() ; working
    //out_of_border(15, 400, 400, 20, 34) ;working
    //out_of_border(1000, 400, 400, 300, 300) ;// working
    model model_obj;
    Data Data_obj;
    //std::vector<std::string> close_char = Data_obj.get_neighbour(id);
    //Data_obj.print_vector(close_char);
    //std::string l = Data_obj.get_value_char("0kfpdq75", 1, "../data/TempChar.csv");
    //std::cout << l << std::endl;
    //l = Data_obj.get_value_char("0kfpdq75", 2, "../data/TempChar.csv");
    //std::cout << l << std::endl;
    //int l = Data_obj.get_index(id, "../data/TempChar.csv");
    //std::cout<< "l" << l << std::endl; 
    //std::string m = std::to_string(15 + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")));
    //std::cout << "m"<< m << std::endl;
    //Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(15 + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))));
    //std::string l = model_obj.get_value(id, 2,  "../data/memory/model/");
    //std::cout << l << std::endl;
    //l = get_random_direction();
    //std::cout << l << std::endl;
    //std::cout << "test " << Data_obj.get_index(id, "../data/TempChar.csv") << std::endl;
    //std::cout << "test " << 10 + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv")) << std::endl;
    //Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 2, std::to_string(10 + std::stoi(Data_obj.get_value_char(id, 2, "../data/TempChar.csv"))), "../data/TempChar.csv");
    //Data_obj.update_csv_cell(Data_obj.get_index(id, "../data/TempChar.csv"), 1, std::to_string(10 + std::stoi(Data_obj.get_value_char(id, 1, "../data/TempChar.csv"))), "../data/TempChar.csv");
    return 0;
}*/
