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
#include <bitset>
#include <cstdint>
#include <exception>
#include <stdexcept>

//g++ reaction.cpp model.cpp ../movement.cpp ../../Data.cpp ../rand.cpp ../calculation.cpp -o debbug_reaction

//dans ce fichier nous definissons tout les actions possibles
//que les entitées peuvent realiser pour faire avancer leur intelligence
//
// 2 type d'action
// - provoquées 
// - non provoquées


//fonction conscientes considérée et pouvant être déclencher par lIA par L'IA

/*
int reaction::get_last_line(const std::string& path) {
    //To do redo
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
*/

reaction::reaction(){

}


int reaction::get_last_line(const std::string& path){
    std::cout << "tool function: get_last_line" << std::endl;
    int count = 0;
    std::ifstream file(path);
    std::string item;

    while(getline(file, item)){
        count ++;
    }
    return count;
}


    std::string reaction::get_value_csv(int l, int value_ind, std::string path) {
        //get any value in csv file, dans une ligne l, et col value_ind
        std::cout << "tool function definition: get_value_csv" << std::endl;
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
    std::cout << "tool function: get_old_stats $id, " << value << std::endl;
    //try{
    Data data_obj;
    //appeler pour garder en mémoire l'ancienne stats pour comparer
    return stoi(data_obj.get_value_char(id, value));
    //}catch(const std::exception& e) {
    //    std::cout << "Caught exception \"" << e.what() << "\"\n";
    //}
    
    return 0;
}

std::string reaction::get_current_action(const std::string& id){
    std::cout << "tool function: get_current_action" << std::endl;
    model mod_obj;
    return mod_obj.get_value(id, 6, "./data/memory/model/" + id + ".dmem");
}


float reaction::result_RI(const std::string& id, float p_stats, int ind, int mult_const, std::string action){
    std::cout << "tool function: result_RI " << std::endl;
    model mod_obj;
    Data data_obj;
    //resultat juge si une action/reaction a été efficaces
    float new_stats = (std::stof(data_obj.get_value_char(id, ind))-p_stats)/ (5 + mult_const); //score evaluation 110 - 100 10/10
    //mult_const = une constante qu'on ajoute pour les stats voulu en ++
    std::unordered_map<std::string, std::string> mem_action;
    std::string mem_map = mod_obj.get_value(id, 8, "./data/memory/model/" + id + ".dmem");
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

    for(int i=1; i<temp.size(); i+=2){
        mem_action.insert(std::make_pair(temp[i-1], temp[i]));
    }

    /* Obsolete nv-^^
    for(int i=0;i<item_map.size();i++){
        try{
            mem_action.insert(std::make_pair(item_map[i], stoi(item_map[i+1])));
        }catch(){
            std::cout << "finished getting, memory actions" << std::endl;
            throw;
        }
    }*/
    
    if(mem_action.find(action) != mem_action.end()){ // pas dans la map
        mem_action.insert(std::make_pair(action, std::to_string(new_stats)));        
    } 

    std::string wback;
    for (const auto& x: mem_action){
        wback += x.first + "," + x.second;
    }
    modify_model_mov(id, "/data/memory/model/" + id + ".dmem", "mem_act="+wback, 8);
    modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4);    
    return 0.0;
}

void reaction::tmp_stats(const std::string& id){ // est appelé 10j plus tard
    //recup les anciennes Stats de temp et les compare pour l'IA
    std::cout << "tool function: tmp_stats" << std::endl;
    model mod_obj;
    std::string paction, pstats, is_pp, ac;
    int sline;
    paction = mod_obj.get_value(id, 5, "./data/memory/model/" + id + ".dmem");
    //on va la chercher dans paction
    std::string line; std::string item;
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    while (std::getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    pstats = tokens[0];
    sline = stoi(tokens[1]);
    is_pp = tokens[2];
    ac = tokens[3];   
    if(is_pp == "true"){
        result_RI(id, stof(pstats), sline, num_generator(8,13), ac);
    }else{
        result_RI(id, stof(pstats), sline, 0, ac);
    }
}

bool reaction::is_sup_attended(const std::string& id){
    //check si c'est une action en ++ 
    std::cout << "tool function: is_sup_attended" << std::endl;
    model mod_obj;
    std::string ent_val = mod_obj.get_value(id, 3, "./data/memory/model/" + id + ".dmem");
    return ent_val.substr(ent_val.size() - 2) == "++";
}


std::string reaction::get_value_choosed(const std::string& id){
    //ancienne reaction de celle qui est choisi
    std::cout << "tool function: get_value_choosed" << std::endl;

    model mod_obj;
    std::string value_choosed = mod_obj.get_value(id, 3, "./data/memory/model/" + id + ".dmem");
    if (is_sup_attended(id)){
        //std::cout << "value choosed : " << value_choosed.substr(0, value_choosed.size()-2) << std::endl;
        return value_choosed.substr(0, value_choosed.size()-2); // return - "++"
    }
    //std::cout << "value choosed no sup: " << value_choosed << std::endl;
    return value_choosed;
}

//break loop collision pour presence

void reaction::reinforcement_intelligence(const std::string& id){
    std::cout << "tool function: reinforcment_intelligence" << std::endl;
    model mod_obj;
    
    //mettre un moyen permettant de ne pas choisir aucune fonction
    //et agir en ne faisant rien de special. C'est a l'entité de choisir ce qu'il veut
        std::unordered_map<std::string, int> target_map{
            {"hap", 3}, {"hea", 2}, 
            {"meH", 5}, {"ang", 9}, 
            {"hyg", 10} };

    std::string get_action = mod_obj.get_value(id, 4, "./data/memory/model/" + id + ".dmem");
    std::string get_searched_stats = mod_obj.get_value(id, 3, "./data/memory/model/" + id + ".dmem");
    std::vector<std::string> action = {"murder", "discrimination", "suicide", "breeding",
    "desir", "isolation", "upmov", "goodconn", "angconn", "anxiety"};

    //std::cout << "target_map[get_value_choosed( id)] " << target_map[get_value_choosed(id)] << std::endl;
    int old_stats = get_old_stats(id, target_map[get_value_choosed(id)]);
    //-std::cout << "break"<< std::endl;
     //prend la value actuelle qui sera l'ancienne 
    bool is_pp = is_sup_attended(id);

    //save dans temp l'ancienne stats, ligne dans le csv, si pp, et l'action 
    //mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "tmp="+old_stats + "," + target_map[get_value_choosed(id)] + "," + is_pp + "," + get_action, 7);  
    modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "paction="+std::to_string(old_stats) + "," + std::to_string(target_map[get_value_choosed(id)]) + "," + std::to_string(is_pp) + "," + get_action, 5);  
    //dans une place temp on save toute les actions
    //avant d'en associer de nouvelles
    modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4);    
    //int const_action = stoi(mod_obj.get_value(id, 4, "./data/memory/model/" + id + ".dmem"));
    bool c = false;
    if (mod_obj.get_value(id, 8, "./data/memory/model/"+id+".dmem") != "null"){
        std::unordered_map<std::string, std::string> hs_mem_act = modval_to_umap(id, 8);
        for (const auto& x: hs_mem_act){
            if(roll_random(55+3*hs_mem_act.size()+stoi(x.second), 0, 210)){
                modify_model_mov(id, "./data/memory/model/"+id+".dmem", "caction="+x.first, 4);
                //on reprend une action precedente
                break;
                c = true;
            }        
        }
    }else if(!c){ //si il n'y a pas d'action en memoire ou si elle n'as pas étét choisi
            modify_model_mov(id, "./data/memory/model/"+id+".dmem", "caction="+action[num_generator(0, 10)], 4);
    }
    
    modify_model_mov(id, "./data/memory/model/"+id+".dmem", "temp="+get_simulation_param(3), 7);
    //on garde le jour pour une certaine frequence
    std::cout << "main tool function reinforcement_intelligence end" << std::endl;
    
    
    /* INUTILE 
    if (mod_obj.get_value(id, 4, "./data/memory/model/" + id + ".dmem") != "null"){ //roll influencer par le nb action presente #8
        if (roll_random(90+const_action, 0, 135)){
            //on role pour savoir si nous reprenons l'action precedente
            //ou si nous cherchons une action efficace - moins ne action est 
            //efficace plus elle sera simplement remplacable (const_action)
            modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,10)], 4);    
        }modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction="+get_action, 4);   
    }else {
        modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction="+action[num_generator(0,4)], 4);
    }   */
  
}

//fonction inconscientes non déclenchées par L'IA
//il faudra les prendres en compte et agir avec clock.cpp 
//ou utiliser une fonction ici qui prend en compte tout les cas et applique
//les nv stats
void reaction::Depression(const std::string& id){
    std::cout << "tool function: Depression" << std::endl;
    Data data_obj;
    model mod_obj;
    int multiplier = 0;
    if (stoi(data_obj.get_value_char(id, 3)) <= 30){
        std::vector<std::string> neigh = data_obj.get_neighbour(id);
        //on recup les voisins et on check ceux qui sont deja depressif
        for (int i=0;i<neigh.size();i++){
            if (mod_obj.get_value(neigh[i], 5, "./data/memory/model/" + id + ".dmem") == "depression"){
                multiplier += num_generator(1,3);
            }
        }
        if(roll_random(35 ,0 ,200 + multiplier + 100 - stoi(data_obj.get_value_char(id, 3)))){
            modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "unconcious=depression", 11);
            //modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction=depression", 4);
        }
    }
}


void reaction::plain_joy(const std::string& id){
    std::cout << "tool function: plain_joy" << std::endl;
    Data data_obj;
    
    int multiplier = 0;
    std::vector<std::string> neigh = data_obj.get_neighbour(id);
    for (int i=0;i<neigh.size();i++){
        multiplier += stoi(data_obj.get_value_char(neigh[i], 3));

    }
     if(roll_random(35, 0,200 + multiplier/neigh.size() + stoi(data_obj.get_value_char(id, 3)))){
        modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "unconcious=joy", 11);
        //modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction=joy", 4);
    }
}

void reaction::crazyness(const std::string& id){
    std::cout << "tool function: crazyness" << std::endl;
    //folie se crée avec la solitude et la baisse de santé mentale
    
    Data Data_obj;
    if(roll_random(25, 0, 200 + 120-stoi(Data_obj.get_value_char(id, 5)) + stoi(Data_obj.get_value_char(id, 7)))){
        modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "unconcious=crazyness", 11);
        //modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction=crazyness", 4);
    }
}


// declencher par le stress baisse le bonheur et la vie
void reaction::anxiety(const std::string& id){
    std::cout << "tool function: anxiety" << std::endl;
    //anxieté se crée vec le stress et le bonheur en baisse
    Data Data_obj;
    if (roll_random(50, 0, 200 + stoi(Data_obj.get_value_char(id, 4)) + 100 - stoi(Data_obj.get_value_char(id, 3)))){
        modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "unconcious=anxiety", 11);
        //modify_model_mov(id, "./data/memory/model/" + id + ".dmem", "caction=anxiety", 4);
    }
}

void reaction::murder(const std::string& id){
    std::cout << "tool function: murder" << std::endl;
    //TODO : a checker
    //horrible ligne -> s'en occupe plus tard
    //action kill some1
    Data data_obj;
    if (data_obj.get_couple(id) != "not"){
        if(roll_random(70, 0, 100)){
            //on roll pour savoir si l'entité veut tuer un ament/e
            //data_obj.app_l("./data/TempChar.csv", data_obj.get_index(data_obj.get_couple(id)));
            //data_obj.app_l("./data/CharacterData.csv", data_obj.get_index(data_obj.get_couple(id)));
            data_obj.eraseFileLine("./data/TempChar.csv", "null", data_obj.get_index(data_obj.get_couple(id)));
            data_obj.eraseFileLine("./data/CharacterData.csv","null", data_obj.get_index(data_obj.get_couple(id)));
            std::cout << "Entity: " << data_obj.get_couple(id) << " has been killed by: "<< id << std::endl;

        }
    }else if (data_obj.point(id) != "not"){
        if (roll_random(40, 0, 110)){
            data_obj.eraseFileLine("./data/TempChar.csv", "null", data_obj.get_index(data_obj.point(id)));
            data_obj.eraseFileLine("./data/CharacterData.csv", "null", data_obj.get_index(data_obj.point(id)));
            std::cout << "Entity: " << data_obj.point(id) << " has been killed by: "<< id << std::endl;
        }
    }
    else{
        std::string killed = get_value_csv(num_generator(1, get_last_line("./data/TempChar.csv")), 0, "./data/TempChar.csv");
        data_obj.eraseFileLine("./data/TempChar.csv", killed, 00);
        data_obj.eraseFileLine("./data/CharacterData.csv", killed, 00);
    }
}

void reaction::suicide(const std::string& id ){
    std::cout << "tool function: suicide" << std::endl;
    //action of entity: suicide
    Data data_obj;
    data_obj.eraseFileLine("./data/TempChar.csv", "null", data_obj.get_index(id));
    data_obj.eraseFileLine("./data/CharacterData.csv", "null", data_obj.get_index(id));
    std::cout << "An entity: " << id << " has commited suicide." << std::endl;
}

void reaction::desire(const std::string& id){
    std::cout << "tool function: desire" << std::endl;
    // level up desire everywhere
    Data data_obj;
    std::vector<std::string> list_couple = data_obj.get_couple_list(id);
    std::vector<std::string> list_point = data_obj.get_point_list(id);
    for (int i=0; i<list_point.size();i++){
        data_obj.modify_desire(id, list_point[i], std::to_string(num_generator(11, 28))); 
    }
        for (int j=0; j<list_couple.size();j++){
        data_obj.modify_desire(id, list_couple[j], std::to_string(num_generator(3, 9))); 
    }

}

void reaction::breeding(const std::string& id){
    std::cout << "tool function: breeding" << std::endl;
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
    std::cout << "tool function: discrimination" << std::endl;
    Data data_obj;
    model mod_obj;
    
    std::unordered_map<std::string, std::string> angconn = 
    modval_to_umap(id, 10);
    //mm chose que l356
    if(roll_random(45, 0, 235)){
        for (const auto& x: angconn){
            if(roll_random(35 + stoi(x.second), 0, 110)){
                std::string killed = get_value_csv(data_obj.get_index(x.first), 1, "./data/CharacterData.csv");
                data_obj.eraseFileLine("./data/TempChar.csv", killed, 00);
                data_obj.eraseFileLine("./data/CharacterData.csv", killed, 00);
            }
        }
    }else{
        for (auto& x : angconn) {
            try {
                int original_value = std::stoi(x.second);
                original_value -= num_generator(4, 11);
                x.second = std::to_string(original_value);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid argument for string to int conversion in pair: " 
                        << x.first << " -> " << x.second << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: Out of range during string to int conversion in pair: " 
                        << x.first << " -> " << x.second << std::endl;
            }
    }
        w_unmap_model(id, angconn, 10);
    }
}
void reaction::w_unmap_model(const std::string& id, std::unordered_map<std::string, std::string> umap, int l){
    std::cout << "tool function: w_unmap_model" << std::endl;
    //write umap to model_file
    model mod_obj;
    std::string conv = mod_obj.get_line_equivalent(id, l, "./data/memory/model/"+id+".dmem") + "=";

    for(const auto& x: umap){
        conv += x.first + "," + x.second + ",";
    }
    //conv += "}";
    modify_model_mov(id, "./data/memory/model/"+ id + ".dmem", conv, 1);
}


std::unordered_map<std::string, std::string> reaction::modval_to_umap(const std::string& id, int line){
    std::cout << "tool function: modval_to_umap" << std::endl;
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

void reaction::ang_social_conn(const std::string& id) {
    std::cout << "tool function: ang_social_conn" << std::endl;
    model mod_obj;
    std::unordered_map<std::string, std::string> angconn = modval_to_umap(id, 10);

    for (auto& x : angconn) {
        try {
            int original_value = std::stoi(x.second);
            original_value -= num_generator(2, 9);
            x.second = std::to_string(original_value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid argument for string to int conversion in pair: " 
                      << x.first << " -> " << x.second << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Out of range during string to int conversion in pair: " 
                      << x.first << " -> " << x.second << std::endl;
        }
    }
    w_unmap_model(id, angconn, 10);
}

void reaction::good_social_conn(const std::string& id){
    std::cout << "tool function: good_social_conn" << std::endl;
    //les liens sociaux commencent à se faire à partir du jour 30
    model mod_obj;
    
    std::unordered_map<std::string, std::string> goodconn = 
    modval_to_umap(id, 9);
    for (auto& x : goodconn) {
        try {
            int original_value = std::stoi(x.second);
            original_value -= num_generator(2, 9);
            x.second = std::to_string(original_value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid argument for string to int conversion in pair: " 
                      << x.first << " -> " << x.second << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Out of range during string to int conversion in pair: " 
                      << x.first << " -> " << x.second << std::endl;
        }
    }
    w_unmap_model(id, goodconn, 9);
}
/*
int main(){    
    reaction obj;
    obj.reinforcement_intelligence("1dgxtc98");
    return 0;
}*/
