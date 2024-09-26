#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include "calculation_software/rand.h"
#include <algorithm>
#include "Data.h"
#include "calculation_software/movement.h"
#include "calculation_software/calculation.h"
#include <string_view>
#include "calculation_software/reinforcement_intelligence/model.h"
//#include "calculation_software/calculation.h"
#include <cstdlib>
#include <tuple>
#include "collision.h"


//check la note en tete movement.cpp
/*
void tempWrite(std::string file, const std::tuple<std::string, std::string, std::string, std::string>& values) {
    std::ofstream file_stream(file + ".asb", std::ios::out | std::ios::app);
    if (file_stream.is_open()) {
        file_stream << std::get<0>(values) << "," << std::get<1>(values) << "," << std::get<2>(values) << "," << std::get<3>(values) << "\n";
        file_stream.close();
    }
}
    void tempWrite(std::string file, const std::vector<std::vector<std::string>>& presence) {
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


void presence() {
    
    std::vector<std::vector<std::vector<int>>> mesh;
        int width =  stoi(get_simulation_param(0));
        int height = stoi(get_simulation_param(1));
        mesh.resize(height, std::vector<std::vector<int>>(width));

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
    }*/

//faire en sorte d'inclure le mental health
//dans d'autre stats comme consequence est cause
//actuellement en constant à et n'influe sur aucune stats
//ligne 113
//Fait :)
    bool is_sick(const std::string& id){ 
        std::cout << "tool function is_sick" << std::endl;
        Data obj;        
        return obj.get_model(id, 1) != "disease=null";
    }


    void CreateTempPosition(const std::string& id, float x, float y, const std::string& gen) {
        std::ofstream fileTemp("./data/TempChar.csv", std::ios::app);
        if (fileTemp.is_open()) {
            fileTemp << id << "," << x << "," << y << "," << gen << "\n";
            fileTemp.close();
        }
    }

    void death(const std::string& id){
        Data data_obj;
        if(stoi(data_obj.get_value_char(id, 2)) <=0){
            data_obj.app_l("./data/CharacterData.csv", data_obj.get_index(id), "");
            data_obj.app_l("./data/TempChar.csv", data_obj.get_index(id), "");
        }
    }

    


    void ch_mod(const std::string& id, const std::string& value){        
        /*
        string line ;
        std::ifstream model(std::to_string("data/memory/model") + id + std::to_string("".dmem"));
        std::getline(model, line);
        std::ofstream model2(std::to_string("data/memory/model") + id + std::to_string(".dmem"));
        model2 << "disease=true" << std::endl;*/
        std::cout << "tool function ch_mod" << std::endl;
        std::ifstream file(std::string("./data/memory/model/") + id + std::string(".dmem"));
        std::vector<std::string> data;
        std::string line;

        while (std::getline(file, line)) {
            data.push_back(line);
        }
        file.close();

        for (const auto& str : data) {
            //std::cout << str << std::endl;
        }

        data[1] = value ;

        std::ofstream outFile(std::string("./data/memory/model/") +id + std::string(".dmem"));
        for (const auto& str : data) {
            outFile << str << std::endl;
        }        
        outFile.close();
    }

    void start_infection(const std::string& id){
        Data obj; 
        if(std::stoi(obj.get_value_char(id, 10)) <= 20){
            if(roll_random(90, 50+(50 - stoi(obj.get_value_char(id, 10))), 370) == true){
                //disease started
                ch_mod(id, "disease=true");
                std::cout << "infection started: " << id << std::endl;
            }
        }
    }
    
        

    void get_id(){
        std::ifstream file("./data/CharacterData.csv");
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> row;
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ',')) {
                row.push_back(word);
            }

            //std::cout << row[0] << std::endl;
            //return row[0];
        }
        std::cout << "Error: bad id/value" << std::endl;
    }

    void immunity(const std::string& id){
        //prepare l'immunité face au maladies
        //TODO: optimize
        model mod_obj;
        std::cout << "Tool function: immunity" << std::endl;
        if (is_sick(id)){            
            //std::cout << "./data/memory/model/" + id + ".dmem" << std::endl;
            std::string im_val = mod_obj.get_value(id, 6, "./data/memory/model/" + id + ".dmem");
            if(im_val == "null"){
                if(roll_random(110, 0, 210)){
                    ch_mod(id, "immune");
                    ch_mod(id, "disease=null");
                }else{
                    ch_mod(id, std::to_string(num_generator(2, 5)));
                }
            }else if (im_val == "immune"){
                if(roll_random(215, 0, 250)){
                    ch_mod(id, "disease=null");
                }
            }else{
                if(roll_random(110+stoi(im_val)*5, 0, 210)){
                    ch_mod(id, "immune");
                    ch_mod(id, "disease=null");
                }
            }
        }
    }
    

void main_loop() {    
    Data obj; // Create an object of Data
    model mod_obj;
    collision collision;
    std::string time_selection = "play";
    int day = collision.get_param(3);
    int tick = 4; // Ensure tick is initialized, or prompt the user to initialize.
    std::cout << "clock starting: " << day << std::endl;

    if (time_selection == "pause") {
        return; // Exit the function if paused
    }

    std::ifstream file("./data/CharacterData.csv");
    std::string line;

    // Skip the header line
    if (getline(file, line)) {
        // Header line is read and discarded
    }

    // Process the remaining lines
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::string word;
        std::stringstream ss(line);
        while (std::getline(ss, word, ',')) {
            row.push_back(word);
        }

        // Process each ID
        std::cout << row[0] << std::endl; // Output the first value of the current row

        int hap_const = num_generator(4,8);
        
        //car de toute facon une entité peut develop des liens avec d'autres
        //m si il est deja en couple
        if (obj.get_value_char(row[0], 13) == "no") {
            obj.start_desire(row[0]);
        } else {
            std::string idB = obj.get_couple(row[0]);
            std::vector<std::string> couples_list;
            if (obj.point(row[0]) != "not") {
                obj.modify_desire(row[0], idB, std::to_string(-num_generator(2, 9)));
                hap_const = -num_generator(5, 14);
            } else if (obj.get_couple_list(row[0]).size() > 1) {
                couples_list = obj.get_couple_list(row[0]);
                for (int i = 0; i < couples_list.size(); i++) {
                    obj.modify_desire(row[0], couples_list[i], std::to_string(-num_generator(2, 11) - (couples_list.size())));
                }
                hap_const = -num_generator(5, 13) - (couples_list.size());
            } else {
                if (obj.procreation(row[0])) {
                    hap_const = num_generator(23, 35);
                    CreateTempPosition(obj.randmId(), stoi(obj.get_value_char(row[0], 1, "./data/TempChar.csv")) + num_generator(3, 5),
                                       stoi(obj.get_value_char(row[0], 2, "./data/TempChar.csv")) + num_generator(3, 5), row[0]);
                }
            }
        }
        
        std::string comm_str = "C:\\Users\\souno\\Desktop\\code\\ASHB.git\\HumanSimulation\\ASHBv0.0.8\\calculation_software\\movement5.exe " + row[0];
        int result = system(comm_str.c_str());


        //std::cout << "error point" << std::endl;
        // Additional logic for processing each row
        if (is_sick(row[0])) {
            if (stoi(obj.get_value_char(row[0], 2)) <= 65) {
                obj.bonheur(row[0], -num_generator(3, 7) - stoi(obj.get_value_char(row[0], 3)) / num_generator(9, 12) + hap_const);
            } else {
                obj.bonheur(row[0], -num_generator(3, 4) - stoi(obj.get_value_char(row[0], 3)) / num_generator(9, 12) + hap_const);
            }
        } else {
            obj.bonheur(row[0], num_generator(7, 13) + hap_const);
        }
        //std::cout << "error point2" << std::endl;
        obj.age_update(row[0], day);
        
        //std::cout << "error point3" << std::endl;
        if (is_sick(row[0])) {
            obj.health(row[0], -num_generator(1, 3) - (99 - stoi(obj.get_value_char(row[0], 5))) / 17);
            if (stoi(obj.get_value_char(row[0], 3)) <= 40) {
                obj.stress(row[0], num_generator(4, 8) + stoi(obj.get_value_char(row[0], 3)) / 8);
            } else {
                obj.stress(row[0], num_generator(3, 9) + stoi(obj.get_value_char(row[0], 3)) / 11);
            }
        } else {
            obj.stress(row[0], -(99 - stoi(obj.get_value_char(row[0], 6))) / 10);
        }


        if (stoi(obj.get_value_char(row[0], 10)) <= 30) {
            obj.health(row[0], -num_generator(2, 7));
        } else if (stoi(obj.get_value_char(row[0], 10)) <= 0) {
            obj.health(row[0], -num_generator(3, 9));
        }else if (stoi(obj.get_value_char(row[0], 2)) <= 150){
            obj.health(row[0], num_generator(5, 11));
        }
        

        if (obj.disease(row[0]) == true) {
            obj.write_logs("this character: " + row[0] + " is now sick");
            ch_mod(row[0], "disease=true");
        }

        

        if (stoi(obj.get_value_char(row[0], 7)) >= 25) {
            obj.mentalhealth(row[0], -num_generator(1, 5));
        } else if (stoi(obj.get_value_char(row[0], 7)) >= 50) {
            obj.mentalhealth(row[0], -num_generator(3, 8));
        } else if (stoi(obj.get_value_char(row[0], 7)) >= 70) {
            obj.mentalhealth(row[0], -num_generator(4, 12));
        }
        //std::cout << "error point7" << std::endl;
        
        

        
        start_infection(row[0]); //on immunise apres le debut de l'infection
        immunity(row[0]);
        immunity(row[0]);

        obj.solitude(row[0]);
        obj.Hygiene(row[0]);
        //std::string coll = "C:\\Users\\LordN\\Desktop\\code\\ASHB\\HumanSimulation\\ASHBv0.0.8\\collision.exe ";
        //int r = system(coll.c_str());
        
        collision.width =  collision.get_param(0);
        collision.height = collision.get_param(1);
    
        collision.separate();
        collision.presence();
        obj.start_desire(row[0]); // on test quand m si on peut start un desire

        obj.desire(row[0], num_generator(3,9), true);
        death(row[0]);
    }

    //day += tick;
    std::cout << "actual day " << day << std::endl;
    std::cout << "actual tick " << tick << std::endl;

    std::cout << "The clock terminated successfully" << std::endl;
    std::cout << "applying the result in the TUI" << std::endl;
}
 
int main() {    
        main_loop();    
    return 0;
}