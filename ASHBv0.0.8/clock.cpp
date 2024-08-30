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
#include <string_view>
#include "calculation_software/reinforcement_intelligence/model.h"
#include "calculation_software/calculation.h"
#include <cstdlib>


//check la note en tete movement.cpp




//faire en sorte d'inclure le mental health
//dans d'autre stats comme consequence est cause
//actuellement en constant à et n'influe sur aucune stats
//ligne 113
//Fait :)
        void sickness(const std::string& id){
        
        /*
        string line ;
        std::ifstream model(std::to_string("data/memory/model") + id + std::to_string("".dmem"));
        std::getline(model, line);
        std::ofstream model2(std::to_string("data/memory/model") + id + std::to_string(".dmem"));
        model2 << "disease=true" << std::endl;*/

        std::ifstream file(std::string("data/memory/model") + id + std::string(".dmem"));
        std::vector<std::string> data;
        std::string line;

        while (std::getline(file, line)) {
            data.push_back(line);
        }
        file.close();

        for (const auto& str : data) {
            std::cout << str << std::endl;
        }

        data[1] = "disease=true\n";

        std::ofstream outFile(std::string("data/memory/model") +id + std::string(".dmem"));
        for (const auto& str : data) {
            outFile << str << std::endl;
        }
        outFile.close();
    }

    bool is_sick(const std::string& id){ 
        Data obj;        
        return obj.get_model(id, 1) != "disease=null";
    }




    void start_infection(const std::string& id){
        Data obj; 
        if(std::stoi(obj.get_value_char(id, 10)) <= 20){
            if(roll_random(130, 50+(50 - stoi(obj.get_value_char(id, 10))), 200) == true){
                //disease started
                sickness(id);
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

            std::cout << row[0] << std::endl;
            //return row[0];
        }
        std::cout << "Error: bad id/value" << std::endl;
    }





    void main_loop(){
        std::cout << "clock starting" <<std::endl;
        int tick; //on doit definir tick ou doit etre def par l'user
        int day = 0;
        Data obj; // Create an object of Data
        //movement mov_obj;
        model mod_obj;
        std::string time_selection = "play";
        //while(true){   
            if (time_selection == "pause"){
                exit(0);
                //si on arrete le temps on sort de la boucle
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

                // Now row[0] will contain the first value of the first data row
                std::cout << row[0] << std::endl; // Output the first value of the current row
                
                //row[0]; // id trouvée dans la boucle
                //on a plus qu'a appelé les fonctions avec cette id 
                //on doit exporter les fonctions puis les appriquées
                

                int hap_const = 3;
                if (obj.get_value_char(row[0], 13) == "no"){ // tente desire
                    obj.start_desire(row[0]);
                    //pas de couple ici


                }else{
                    std::string idB = obj.get_couple(row[0]);
                    std::vector<std::string> couples_list;
                    if (obj.point(row[0]) != "not"){
                        //ici row[0] = id, cherche a créer un couple avec une
                        //autre personne
                        obj.modify_desire(row[0], idB, std::to_string(-num_generator(2, 9)));
                        hap_const = -num_generator(5, 16);
                    
                        }else if (obj.get_couple_list(row[0]).size() > 1){
                        couples_list = obj.get_couple_list(row[0]);
                        //ici row[0] a plus d'un couple, don il/elle a trompé
                        for (int i=0; i<couples_list.size(); i++){
                            obj.modify_desire(row[0], couples_list[i], std::to_string(-num_generator(2, 11) -(couples_list.size())));
                        }
                        //on reduit le desire de tout les couples auquelles row[0] est(-) ou
                        //est entrain de créer (>)  
                        hap_const = -num_generator(7, 17) -(couples_list.size());

                    }else{  
                        if(obj.procreation(row[0])){
                            hap_const = num_generator(9, 18);
                        }
                    }             
                }   

                
                //int mov_exe = system("calculation_software/movement.exe " + row[0]);                
                //single_char_movement(row[0]);



                // /!\ YOU NEED TO CHANGE comm_str value /!\ 
                // it need to be the absolute path to folder calculation software
                //unless it movement.cpp will not work => all movement

                std::string comm_str = "C:\\Users\\LordN\\Desktop\\code\\ASHB\\HumanSimulation\\ASHBv0.0.8\\calculation_software\\movement2.exe " + row[0];
                //Change this value    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  
//
                std::cout << comm_str << std::endl;
                std::cout << "id supposable" << row[0] << std::endl;
//
                int result = system(comm_str.c_str());
                
                
                std::cout << "hap const" << hap_const << std::endl;
                if(is_sick(row[0])){
                    std::cout << "entity is sick" << std::endl;
                    
                    if (stoi(obj.get_value_char(row[0], 2)) <= 65){
                        obj.bonheur(row[0], -num_generator(2, 6) -stoi(obj.get_value_char(row[0],3))/num_generator(8, 12) + hap_const);
                    }else{
                        obj.bonheur(row[0], -num_generator(1, 2) -stoi(obj.get_value_char(row[0],3))/num_generator(8, 12) + hap_const);
                    }                    
                }else{
                    obj.bonheur(row[0], num_generator(4, 10) + hap_const);
                }
                 

                obj.age_update(row[0], day);


                
                if (is_sick(row[0])){
                    obj.health(row[0], -3.4 - (99 - stoi(obj.get_value_char(row[0], 6)))/10); //vie

                    //stress depend du bonheur
                    if (stoi(obj.get_value_char(row[0],3)) <= 40){
                         obj.stress(row[0], 5 + stoi(obj.get_value_char(row[0],3))/10);
                    } else{
                        obj.stress(row[0], 5 + stoi(obj.get_value_char(row[0],3))/15);
                    }
                }else{
                     obj.stress(row[0], - (99 - stoi(obj.get_value_char(row[0], 6)))/10);
                }


                
                if (obj.disease(row[0]) == true){ 
                    std::cout << "this character: " << row[0] << "is now sick" << std::endl;
                    sickness(row[0]);
                }
                if(stoi(obj.get_value_char(row[0], 7)) >= 25){
                    obj.mentalhealth(row[0], -num_generator(1, 3));
                }else if (stoi(obj.get_value_char(row[0], 7)) >= 50){
                    obj.mentalhealth(row[0], -num_generator(3,5));
                }else if (stoi(obj.get_value_char(row[0], 7)) >= 70){
                    obj.mentalhealth(row[0], -num_generator(4, 11));
                }


                
                start_infection(row[0]);
                obj.solitude(row[0]);
                obj.Hygiene(row[0]);

                //if(obj.procreation(row[0]) == true){
                    //procreation reussi
                //}

                //faire les émotions après
            //}
            //on appliqué toute les fonctions aux diff id
            //on change de jour
            day+= tick;
            std::cout << "actual day " << day << std::endl;
            std::cout << "actual tick " << tick << std::endl;
            

        }
        std::cout << "the clock terminated sucessfully" << std::endl;
        std::cout << "applying the result in the GUI/UI" << std::endl;
    }

 
int main() {
    
        main_loop();
    
    
    return 0;
}