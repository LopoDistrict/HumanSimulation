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

reaction::reaction(){
    Data data_obj;
    model mod_obj;
    movement mov;
}

//dans ce fichier nous definissons tout les actions possibles
//que les entitées peuvent realiser pour faire avancer leur intelligence
//
// 2 type d'action
// - provoquées 
// - non provoquées

//fonction conscientes déclenchées par L'IA
void murder
void discrimination //heritage
void suicide //why not
void breeding // reproduction peut peut etre augmenter la stats attendu
void desir // le fait d'avoir du desir avec plusieurs femmes 
void isolation // écart a la soupe initial


//fonction utile pour le fonctionnement de L'IA
int get_old_stats(const& std::string id, int value){
    //appeler pour garder en mémoire l'ancienne stats pour comparer
    return data_obj.get_value_char(id, value);
}

std::string get_current_action(const& std::string id){
    return mod_obj.get_value(id, 6);
}

float result_RI(const& std::string id, float prec_stats, int ind, int mult_const){
    //le resultat est rendu selon un float de -10 a 10 
    //jugeant si une action/reaction a été efficaces
    float new_stats = stof(data_obj.get_value_char(id, ind));
    //pour obtenir le score d'evolution     
    return (new_stats-prec_stats)/ (5 + mult_const); //  110 - 100 10/10
    //mult_const = une constante qu'on ajoute pour les stats voulu en ++
}

bool is_sup_attended(const& std::string id){
    //check si c'est une action en ++ 
    return mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem").substr(2) == "++";
}


void get_value_choosed(const& std::string id){

    if (is_sup_attended()){
        return mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem") - "++";
    }
    return mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem");
}  

void reinforcement_intelligence(const& std::string id){
    //mettre un moyen permettant de ne pas choisir aucune fonction
    //et agir en ne faisant rien de special. C'est a l'entité de choisir ce qu'il veut
    std::string get_action = mod_obj.get_value(id, 6, "../../data/memory/model/" + id + ".dmem");
    std::string get_searched_stats = mod_obj.get_value(id, 3, "../../data/memory/model/" + id + ".dmem");
    std::vector<std::string> action = {"murder", "discrimination", "suicide", "breeding",
    "desir", "isolation"};
    int const_action = stoi(mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "action="+action[num_generator(0,4)], 6));    
    
    if (mod_obj.get_value(id, 6, "../../data/memory/model/" + id + ".dmem") != "null"){
        if (roll_random(90+const_action, 0, 135)){
            //on role pour savoir si nous reprenons l'action precedente
            //ou si nous cherchons une action efficace - moins ne action est 
            //efficace plus elle sera simplement remplacable (const_action)
            mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "action="+action[num_generator(0,4)], 6);    
        }
        int old_stats = get_old_stats(id, )
    }else {
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "action="+action[num_generator(0,4)], 6);
    }

}


//fonction inconscientes non déclenchées par L'IA
//il faudra les prendres en compte et agir avec clock.cpp 
//ou utiliser une fonction ici qui prend en compte tout les cas et applique
//les nv stats
void reaction::Depression(const& std::string id){
    int multiplier = 0;
    if ( data_obj.get_value_char(id, 3) <= 30){
        std::vector<std::string> neigh = data_obj.get_neighbour(id):
        //on recup les voisins et on check ceux qui sont deja depressif
        for (int i=0;i<neigh.size();i++){
            if (mod_obj.get_value(neigh[i], 5) == "depression"){
                multiplier += num_generator(1,3);
            }
        }
        if(roll_random(35 ,0 ,200 + multiplier + 100 - stoi(data_obj.get_value_char(id, 3)))){
            mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=depression", 5);
        }
    }
}

void reaction::plain_joy(const& std::string id){
    int multiplier = 0;
    std::vector<std::string> neigh = data_obj.get_neighbour(id):
    for (int i=0;i<neigh.size();i++){
        multiplier += stoi(data_obj.get_value_char(neigh[i], 3));

    }
     if(roll_random(35, 0,200 + multiplier/neigh.size() + stoi(data_obj.get_value_char(id, 3)))){
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=joy");
    }
}

void reaction::crazyness(const& std::string id){
    //folie se crée avec la solitude et la baisse de santé mentale
    if(roll_random(25, 0, 200 + 120-data_obj.get_value_char(id, 5) + data_obj.get_value_char(id, 7))){
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=crazyness");
    }
}

// declencher par le stress baisse le bonheur et la vie
void anxiety(const& std::string id){
    //anxieté se crée vec le stress et le bonheur en baisse
    if (roll_random(50, 0, 200 + stoi(data_obj.get_value_char(id, 4)) + 100 - stoi(data_obj.get_value_char(id, 3)))){
        mov.modify_model_mov(id, "../../data/memory/model/" + id + ".dmem", "unconcious=anxiety");
    }

}
/*
void rage(const& std::string id){
    int multiplier = 0;

}
*/

/*
int main(){
    return 0;
}
*/