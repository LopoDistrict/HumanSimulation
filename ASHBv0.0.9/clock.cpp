#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include "calculation_software/rand.h"
//#include <algorithm>
#include "Data.h"
#include "calculation_software/movement.h"
//#include "calculation_software/calculation.h"
//#include <string_view>
#include "calculation_software/reinforcement_intelligence/model.h"
#include "calculation_software/reinforcement_intelligence/reaction.h"
#include <cstdlib>
//#include <tuple>
#include <cmath>
#include "collision.h"
#include <sys/stat.h>
#include <unistd.h>
//#include <thread>

//#include "calculation_software/include/fast_division.h"

/*g++ clock.cpp calculation_software/rand.cpp Data.cpp calculation_software/movement.cpp calculation_software/calculation.cpp calculation_software/reinforcement_intelligence/model.cpp collision.cpp calculation_software/reinforcement_intelligence/reaction.cpp -o clock6_debbug */
//g++ -shared -o libadd.so -fPIC clock.cpp calculation_software/rand.cpp Data.cpp calculation_software/movement.cpp calculation_software/calculation.cpp calculation_software/reinforcement_intelligence/model.cpp collision.cpp


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
            return obj.get_model(id, 1) == "disease=null";
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
                data_obj.eraseFileLine("./data/CharacterData.csv", "null",data_obj.get_index(id)+1);
                data_obj.eraseFileLine("./data/TempChar.csv", "null",data_obj.get_index(id)+1);
                data_obj.write_main_logs("entity died: " + id);
                std::cout << id << "has died" << std::endl;
            } 
        }
            


    void chmod(const std::string& id, const std::string& value, int l) {
        std::cout << "Tool function: modify_model_mov" << std::endl;
        std::ifstream file("./data/memory/model/" + id + ".dmem");
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
        std::ofstream filew("./data/memory/model/" + id + ".dmem");
        for (size_t i = 0; i < lines.size(); ++i) {
            filew << lines[i];
            if (i < lines.size() - 1) {
                filew << std::endl; // Add newline for all lines except the last one
            }
        }
        filew.close();
    }

        void start_infection(const std::string& id){
            std::cout << "start_infection" << std::endl;
            collision collision;
            Data obj; 
            int mpier;
            if(collision.get_param(2) == "arid"){mpier = 2;}
            else if(collision.get_param(2) == "oceanic"){mpier = 3;}
            else{mpier = 4;}
            if(std::stoi(obj.get_value_char(id, 10)) <= 20){
                if(roll_random(abs(stoi(obj.get_value_char(id, 10)) + (num_generator(5,9)*mpier)) ,0, 460) == true){
                    //disease started
                    chmod(id, "disease=true", 1);
                    std::cout << "infection started: " << id << std::endl;
                    obj.write_main_logs("infection started with: " + id);
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
            }
            std::cout << "Error: bad id/value" << std::endl;
        }

        inline bool file_exist (const std::string& name) {
            struct stat buffer;   
            return (stat (name.c_str(), &buffer) == 0); 
        }

        void implem_reaction(const std::string& id, int day){
            //Le processus du machine learning doit prendre plusieurs jours et 
            //ne s'exec donc pas tt les jours
            reaction react_obj;
            model mod_obj;

            //décalage de 10 jours entre chaque decision => a faire varier close to 10 jours 
            //car toute les entités vont tous des comportements differents à un même moment donné
            if (mod_obj.get_value(id, 7, "./data/memory/model/"+ id + ".dmem") == "null"){
                //le cycle a été fini l214 ou il n'a pas été encore fait
                react_obj.reinforcement_intelligence(id);
                //l'action est apelé dans reaction.cpp
            }
            if (stoi(mod_obj.get_value(id, 7, "./data/memory/model/" + id + ".dmem"))+num_generator(8, 12) >= day){
                react_obj.recup_compare(id); //ce nom de fonction est contre intuitif et stupide xd
                
                modify_model_mov(id, "./data/memory/model/"+id+".dmem", "temp=null", 7);                
            }
            
        }

        void immunity(const std::string& id){
            //prepare l'immunité face au maladies
            //TODO: optimize
            model mod_obj;
            std::cout << "Tool function: immunity" << std::endl;
            if (is_sick(id)){            
                std::string im_val(mod_obj.get_value(id, 6, "./data/memory/model/" + id + ".dmem"));
                if(im_val == "null"){
                    if(roll_random(40, 0, 470)){
                        std::cout << "entity immune"<< id << std::endl;
                        chmod(id, "immunity=immune", 6);
                        chmod(id, "disease=null", 1);
                    }else{
                        chmod(id, "immunity=" + std::to_string(num_generator(2, 5)), 6);
                    }
                }else if (im_val == "immune"){
                    if(roll_random(215, 0, 390)){
                        chmod(id, "disease=null", 1);
                    }
                }else{
                    if(roll_random(70+stoi(im_val), 0, 470)){
                        chmod(id, "immunity=immune", 6);
                        chmod(id, "disease=null", 1);
                    }
                }
            }
        }

// 
    void main_loop() {    
        Data obj; 
        model mod_obj;
        collision collision;
        std::string time_selection = "play";
        int day = stoi(collision.get_param(3));
        int tick = 4; // Ensure tick is initialized, or prompt the user to initialize.

        std::cout << "clock starting, day: " << day << std::endl;

        if (time_selection == "pause") {
            return; // Exit the function if paused
        }
        std::ifstream file("./data/CharacterData.csv");
        std::string line;

        // Skip the header line
        if (getline(file, line)) {
           
        }

        // Process the remaining lines
        while (getline(file, line)) {
            std::vector<std::string> row;
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ',')) {
                row.push_back(word);
            }

            int hap_const = num_generator(0,4);

            //car de toute facon une entité peut develop des liens avec d'autres
            //m si il est deja en couple
            if (obj.get_value_char(row[0], 13) == "no") {
                obj.start_desire(row[0]);
            } else {                
                std::string idB = obj.get_couple(row[0]);
                std::vector<std::string> couples_list;
                if (obj.point(row[0]) != "not") {
                    obj.modify_desire(row[0], idB, std::to_string(-num_generator(2, 9)));
                    hap_const = -num_generator(5, 11);
                } else if (obj.get_couple_list(row[0]).size() > 1) {
                    couples_list = obj.get_couple_list(row[0]);
                    for (int i = 0; i < couples_list.size(); i++) {
                        obj.modify_desire(row[0], couples_list[i], std::to_string(-num_generator(2, 11) - (couples_list.size())));
                    }
                    hap_const = -num_generator(6, 10) - (couples_list.size());
                } else {
                    if (obj.procreation(row[0])) {
                        hap_const = num_generator(24, 47);
                        // les 2 entités deviennent parents donc ++++
                        CreateTempPosition(obj.randmId(), stoi(obj.get_value_char(row[0], 1, "./data/TempChar.csv")) + num_generator(3, 5),
                                        stoi(obj.get_value_char(row[0], 2, "./data/TempChar.csv")) + num_generator(3, 5), row[0]);
                    }
                }
            }
            //sep1
            
            std::string comm_str = "calculation_software\\movement5.exe " + row[0];
            int result = system(comm_str.c_str());

            //solution temporaire
            //implem_reaction(row[0], day);
            //implementaton renforcment learning

            //sep
            
            if (is_sick(row[0])) {
                if (stoi(obj.get_value_char(row[0], 2)) <= 65) {
                    //obj.bonheur(row[0], -num_generator(3, 7) - stoi(obj.get_value_char(row[0], 3)) / num_generator(9, 12) + hap_const);
                    obj.bonheur(row[0], -num_generator(3, 6) - obj.fastdiv(stoi(obj.get_value_char(row[0], 3)), 1.0 * num_generator(6, 9)) + hap_const);
                } else {                
                    //obj.bonheur(row[0], -num_generator(3, 4) - stoi(obj.get_value_char(row[0], 3)) / num_generator(9, 12) + hap_const);
                    obj.bonheur(row[0], -num_generator(3, 5) - obj.fastdiv(stoi(obj.get_value_char(row[0], 3)),1.0 * num_generator(6, 9)) + hap_const);
                }
            } else {
                obj.bonheur(row[0], num_generator(2, 7) + hap_const);
            }
            obj.age_update(row[0], day);
            //sep1
            
            if (is_sick(row[0])) {
                //obj.health(row[0], -num_generator(1, 3) - (99 - stoi(obj.get_value_char(row[0], 5))) / 19);
                obj.health(row[0], -num_generator(5, 14) - obj.fastdiv(stoi(obj.get_value_char(row[0], 5)), 3.6));

                if (stoi(obj.get_value_char(row[0], 3)) <= 40) {
                    //obj.stress(row[0], num_generator(4, 8) + stoi(obj.get_value_char(row[0], 3)) / 8);
                    obj.stress(row[0], num_generator(4, 11) + obj.fastdiv(stoi(obj.get_value_char(row[0], 3)), 5.3));
                } else {
                    //obj.stress(row[0], num_generator(3, 9) + stoi(obj.get_value_char(row[0], 3)) / 11);
                    obj.stress(row[0], num_generator(3, 11) + obj.fastdiv(stoi(obj.get_value_char(row[0], 3)), 10.0));
                }
                immunity(row[0]);
            } else {
                //obj.stress(row[0], -(99 - stoi(obj.get_value_char(row[0], 6))) / 10);
                obj.stress(row[0], -(obj.fastdiv(99 - stoi(obj.get_value_char(row[0], 6)), 10.0)));
                if (obj.disease(row[0])) {            
                    chmod(row[0], "disease=true", 1);                     
                }                  
            }
            if (stoi(obj.get_value_char(row[0], 10)) <= 30) {
                obj.health(row[0], -num_generator(4, 8));

            } else if (stoi(obj.get_value_char(row[0], 10)) <= 0) {
                obj.health(row[0], -num_generator(6, 8));

            // on suppose que la guérison est rapide
            }else if (stoi(obj.get_value_char(row[0], 2)) <= 40){
                obj.health(row[0], num_generator(9, 14));

            }else if (stoi(obj.get_value_char(row[0], 2)) <= 120){
                obj.health(row[0], num_generator(2, 3));
            }

            obj.health(row[0], num_generator(-10, 5));

            if (stoi(obj.get_value_char(row[0], 7)) >= 25) {
                obj.mentalhealth(row[0], -num_generator(2, 7));
            } else if (stoi(obj.get_value_char(row[0], 7)) >= 50) {
                obj.mentalhealth(row[0], -num_generator(5, 11));
            } else if (stoi(obj.get_value_char(row[0], 7)) >= 70) {
                obj.mentalhealth(row[0], -num_generator(6, 12));
            }

            start_infection(row[0]); //on immunise apres le debut de l'infection
            

            obj.solitude(row[0]);
            obj.Hygiene(row[0]);
            //std::string coll = "C:\\Users\\LordN\\Desktop\\code\\ASHB\\HumanSimulation\\ASHBv0.0.8\\collision.exe ";
            //int r = system(coll.c_str());
            
            obj.start_desire(row[0]); // on test quand m si on peut start un desire

            try{
                //somehow desire cannot work sometimes :/
                obj.desire(row[0], num_generator(2,8), false);
            } catch (const std::exception& e){
                std::cout << e.what() << std::endl;
            }
            
            death(row[0]);

            //std::vector<std::string> point_lst = obj.get_point_list(row[0]);
            //for (int i=0;i<point_lst.size();i++){
            //    if(roll_random(stoi(obj.get_desire_single(row[0], point_lst[i])), 0, 225)){
            //        obj.start_couple(row[0], point_lst[i]);
            //    }else{
            //        obj.modify_desire(row[0], point_lst[i], std::to_string(num_generator(1,4)));
            //    }                    
            //}
            
            collision.width =  stoi(collision.get_param(0));
            collision.height = stoi(collision.get_param(1));            
            
            if (!file_exist("./data/temp/tempSeparation.asb")){
                collision.separate();             
            }
            collision.presence();
            // sep3            
        }
    }

    
    int main() {    
        collision collision;
        int day = stoi(collision.get_param(3));
        int tick = 4; 

        main_loop();
        std::cout << "actual day " << day << std::endl;
        std::cout << "actual tick " << tick << std::endl;

        std::cout << "The clock terminated successfully" << std::endl;
        std::cout << "applying the result in the TUI" << std::endl;

        
        return 0;
    }

