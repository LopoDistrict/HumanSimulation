#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "../../Data.h"
#include "../rand.h"
#include "model.h"
#include "../movement.h"
#include <unordered_map>
#include "reaction.h"
#include <cstring>





//dans ce fichier nous definissons tout les actions possibles
//que les entitées peuvent realiser pour faire avancer leur intelligence
//
// 2 type d'action
// - provoquées 
// - non provoquées


//fonction conscientes déclenchées par L'IA
std::string reaction::get_last_line(const std::string& path) {
    boost::iostreams::mapped_file mmap("input.txt", boost::iostreams::mapped_file::readonly);
    const char* f = mmap.const_data();
    const char* l = f + mmap.size();
    uintmax_t lineCount = 0;

    while (f && f != l) {
        if ((f = static_cast<const char*>(memchr(f, '\n', l - f)))) {
            lineCount++;
            f++; // Move past the newline character
        }
    }
    std::cout << "Total lines: " << lineCount << std::endl;
    return lineCount;
}

    std::string reaction::get_value_csv(int l, int value_ind, std::string path) {
        std::cout << "tool function definition: get_value_char" << std::endl;
        std::cout << value_ind << std::endl;
        std::ifstream file(path);
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> row;
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ',')) {
                row.push_back(word);
            }
            if (row.size()-1 == l) {
                std::cout << row[value_ind] << std::endl;
                return row[value_ind];
            }
        }
        return "Error: bad id/value";
    }


//fonction utile pour le fonctionnement de L'IA
int reaction::get_old_stats(const std::string& id, int value){
    Data data_obj;
    //appeler pour garder en mémoire l'ancienne stats pour comparer
    return stoi(data_obj.get_value_char(id, value));
}

std::string reaction::get_current_action(const std::string& id){
    model mod_obj;
    return mod_obj.get_value(id, 6, "./data/memory/model/" + id + ".dmem");
}


float reaction::result_RI(const std::string& id, float p_stats, int ind, int mult_const, std::string action){
    
    model mod_obj;
    Data data_obj;
    //resultat juge si une action/reaction a été efficaces
    float new_stats = (std::stof(data_obj.get_value_char(id, ind))-p_stats)/ (5 + mult_const) //score evaluation 110 - 100 10/10
    //mult_const = une constante qu'on ajoute pour les stats voulu en ++
    std::unordered_map<std::string, int> mem_action;
    std::string mem_map = mod_obj.get_value(id, 8, "../../data/memory/model/" + id + ".dmem");
    std::string item_map;
    std::stringstream ssmap(mem_map);
    std::stringstream ss(action);
    std::string item;
    std::vector<std::string> tokens;
    //TODO: a opti, utilise un vector pour transfert d'info
    std::vector<std::string> temp;
    while(std::getline(ssmap, item_map, ',')){ // mem_act=breeding,4,murder,10,desire,-5
        temp.push_back(item_map);
    }

    for(int i=0;i<item_map.size();i++){
        try{
            mem_action.insert(std::make_pair(item_map[i], stoi(item_map[i+1])));
        }catch("Err"){
            std::cout << "finished getting, memory actions" << std::endl;
        }
    }
    
    if(!mem_action.find(action) == mem_action.end()){ // pas dans la map
        mem_action.insert(std::make_pair(action, new_stats));        
    } 

    std::string wback;
    for (const auto& x: mem_action){
        wback += x.first + "," + x.second;
    }
    mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "mem_act="+wback, 8);
    stoi(mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4));    
}

void reaction::tmp_stats(const std::string& id){ // est appelé 10j plus tard
    //recup les anciennes Stats de temp et les compare pour l'IA
    model mod_obj;
    std::string paction, pstats, sline, is_pp, ac;
    paction = mod_obj.get_value(id, 8, "../../data/memory/model/" + id + ".dmem");
    //on va la chercher dans paction
    std::string line;
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    while (std::getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    pstats = tokens[0];
    sline = tokens[1];
    is_pp = tokens[2];
    ac = tokens[3];   
    if(is_pp == "true"){
        result_RI(id, pstats, sline, num_generator(8,13), ac);
    }else{
        result_RI(id, pstats, sline, 0, ac);
    }
}

bool reaction::is_sup_attended(const std::string& id){
    //check si c'est une action en ++ 
    model mod_obj;
    return mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem").substr(2) == "++";
}


std::string reaction::get_value_choosed(const std::string& id){
    model mod_obj;
    if (is_sup_attended(id)){
        return mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem") - std::to_string("++");
    }
    return mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem");
}

//break loop collision pour presence

void reaction::reinforcement_intelligence(const std::string& id){
    model mod_obj;
    
    //mettre un moyen permettant de ne pas choisir aucune fonction
    //et agir en ne faisant rien de special. C'est a l'entité de choisir ce qu'il veut
        std::unordered_map<std::string, std::string> target_map{
        {"hap", "3"}, {"hea", 2}, {"meH", 5}, {"ang", 9}, {"hyg", 10}
    }
    std::string get_action = mod_obj.get_value(id, 4, "../../data/memory/model/" + id + ".dmem");
    std::string get_searched_stats = mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem");
    std::vector<std::string> action = {"murder", "discrimination", "suicide", "breeding",
    "desir", "isolation", "upmov", "goodconn", "angconn", "anxiety"};


    int old_stats = get_old_stats(id, target_map[get_value_choosed(id)]); //prend la value actuelle qui sera l'ancienne 
    bool is_pp = is_sup_attended(id);

    //save dans temp l'ancienne stats, ligne dans le csv, si pp, et l'action 
    //mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "tmp="+old_stats + "," + target_map[get_value_choosed(id)] + "," + is_pp + "," + get_action, 7);  
    mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "paction="+old_stats + "," + target_map[get_value_choosed(id)] + "," + is_pp + "," + get_action, 5);  
    //dans une place temp on save toute les actions
    //avant d'en associer de nouvelles

    int const_action = stoi(mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4));    
    if (mod_obj.get_value(id, 4, "../../data/memory/model/" + id + ".dmem") != "null"){ //roll influencer par le nb action presente #8
        if (roll_random(90+const_action, 0, 135)){
            //on role pour savoir si nous reprenons l'action precedente
            //ou si nous cherchons une action efficace - moins ne action est 
            //efficace plus elle sera simplement remplacable (const_action)
            mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4);    
        }mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "caction="+get_action, 4);    
                 
    }else {
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4);
    }   
}

//fonction inconscientes non déclenchées par L'IA
//il faudra les prendres en compte et agir avec clock.cpp 
//ou utiliser une fonction ici qui prend en compte tout les cas et applique
//les nv stats
void reaction::Depression(const std::string& id){
    Data data_obj;
    int multiplier = 0;
    if (stoi(data_obj.get_value_char(id, 3)) <= 30){
        std::vector<std::string> neigh = data_obj.get_neighbour(id);
        //on recup les voisins et on check ceux qui sont deja depressif
        for (int i=0;i<neigh.size();i++){
            if (mod_obj.get_value(neigh[i], 5, "../../data/memory/model/" + id + ".dmem") == "depression"){
                multiplier += num_generator(1,3);
            }
        }
        if(roll_random(35 ,0 ,200 + multiplier + 100 - stoi(data_obj.get_value_char(id, 3)))){
            mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=depression", 5);
        }
    }
}


void reaction::plain_joy(const std::string& id){
    Data data_obj;
    
    int multiplier = 0;
    std::vector<std::string> neigh = data_obj.get_neighbour(id);
    for (int i=0;i<neigh.size();i++){
        multiplier += stoi(data_obj.get_value_char(neigh[i], 3));

    }
     if(roll_random(35, 0,200 + multiplier/neigh.size() + stoi(data_obj.get_value_char(id, 3)))){
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=joy");
    }
}

void reaction::crazyness(const std::string& id){
    //folie se crée avec la solitude et la baisse de santé mentale
    
    Data Data_obj;
    if(roll_random(25, 0, 200 + 120-stoi(data_obj.get_value_char(id, 5)) + data_obj.get_value_char(id, 7))){
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=crazyness");
    }
}


// declencher par le stress baisse le bonheur et la vie
void reaction::anxiety(const std::string& id){
    //anxieté se crée vec le stress et le bonheur en baisse
    
    if (roll_random(50, 0, 200 + stoi(data_obj.get_value_char(id, 4)) + 100 - stoi(data_obj.get_value_char(id, 3)))){
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=anxiety");
    }

}

void reaction::murder(const std::string& id){
    //horrible ligne -> s'en occupe plus tard
    Data data_obj;
    if (data_obj.get_couple(id) != "not"){
        if(roll_random(70, 0, 100)){
            //on roll pour savoir si l'entité veut tuer un ament/e
            data_obj.app_l("./data/TempChar.csv", data_obj.get_index(data_obj.get_couple(id)));
            data_obj.app_l("./data/CharacterData.csv", data_obj.get_index(data_obj.get_couple(id)));
            std::cout << "Entity: " << data_obj.get_couple(id) << " has been killed by: "<< id << std::endl;
        }
    }else if (data_obj.point(id) != "not"){
        if (roll_random(40, 0, 110)){
            data_obj.app_l("./data/TempChar.csv", data_obj.get_index(data_obj.point(id)));
            data_obj.app_l("./data/CharacterData.csv", data_obj.get_index(data_obj.point(id)));
            std::cout << "Entity: " << data_obj.point(id) << " has been killed by: "<< id << std::endl;
        }
    }
    else{
        std::string killed = get_value_csv(num_generator(1, get_last_line("./data/TempChar.csv")));
        data_obj.app_l("./data/TempChar.csv", killed);
        data_obj.app_l("./data/CharacterData.csv", killed);
    }
}

void reaction::suicide(const std::string& id ){
    Data data_obj;
    data_obj.app_l("./data/TempChar.csv", data_obj.get_index(id));
    data_obj.app_l("./data/CharacterData.csv", data_obj.get_index(id));
    std::cout << "An entity: " << id << " has commited suicide." << std::endl;
}

void reaction::desire(const std::string& id){
    Data data_obj;
    std::vector<std::string> list_couple = data_obj.get_couple_list(id, );
    std::vector<std::string> list_point = data_obj.get_point_list(id);
    for (int i=0; i<list_point.size();i++){
        data_obj.modify_desire(id, list_point[i], num_generator(11, 28)); 
    }
        for (int j=0; j<list_couple.size();j++){
        data_obj.modify_desire(id, list_couple[j], num_generator(3, 9)); 
    }

}

void reaction::breeding(const std::string& id){
    Data data_obj;
    //on provoque (ou on augmente les chances) la procreation
     //des entitées encouple avec l'entité désigné
    data_obj.procreation(id, 20);
}


//void discrimination //heritage 
//void breeding // reproduction peut peut etre augmenter la stats attendu
//void desire // le fait d'avoir du desir avec plusieurs femmes 
//void isolation() // écart a la soupe initial
/*
//TODO
int reaction::upmov(const std::string& id){
    //fonction inutile car un appel peut être fait
    //temp juste pour reference 
    //le int return est le nb de mvt en plus que l'entité va faire
    return num_generator(1,3);

}
*/
void reaction::discrimination(const std::string& id){
    Data data_obj;
    model mod_obj;
    
    std::unordered_map<std::string, std::string> angconn = 
    mod_obj.get_value(id, 10, "./data/memory/model/"+id+".dmem");
    if(roll_random(45, 0, 235)){
        for (const auto& x: angconn){
            if(roll_random(35 + std::string(x.second), 0, 110))
            std::string killed = data_obj.get_value_csv(x.first);
            data_obj.app_l("./data/TempChar.csv", killed);
            data_obj.app_l("./data/CharacterData.csv", killed);
        }
    }else{
        for (const auto& x: angconn){
            x.second -= num_generator(4, 11);
        }
        mov.modify_model_mov(id, "./data/memory/model/"+id+".dmem", std::to_string(angconn), 10);
    }
}

void reaction::ang_social_conn(const std::string& id){
    //les liens sociaux commencent à se faire à partir du jour 30
    model mod_obj;
    std::unordered_map<std::string, std::string> angconn = 
        mod_obj.get_value(id, 10, "./data/memory/model/"+id+".dmem");
        //to check err: string dans unordored map
    for(const auto& x: angconn){
        x.second -= num_generator(2, 9);
    }
    mov.modify_model_mov(id, "./data/memory/model/"+id+".dmem", std::to_string(angconn), 10);
}

void reaction::good_social_conn(const std::string& id){
    //les liens sociaux commencent à se faire à partir du jour 30
    model mod_obj;
    
    std::unordered_map<std::string, std::string> goodconn = 
    mod_obj.get_value(id, 10, "./data/memory/model/"+id+".dmem");
    for(const auto& x: goodconn){
        x.second += num_generator(2, 9);
    }
    mov.modify_model_mov(id, "./data/memory/model/"+id+".dmem", std::to_string(goodconn), 10);
}

