#ifndef REACTION_H
#define REACTION_H
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
#include <bitset>
#include <cstdint>


class reaction {
public:
    reaction();
    int get_last_line(const std::string& path);
    std::string get_value_csv(int l, int value_ind, std::string path);
    void murder(const std::string& id);
    void suicide(const std::string& id );
    void desire(const std::string& id);
    void breeding(const std::string& id);
    int get_old_stats(const std::string& id, int value);
    std::string get_current_action(const std::string& id);
    float result_RI(const std::string& id, float p_stats, int ind, int mult_const, std::string action);
    bool is_sup_attended(const std::string& id);
    std::string get_value_choosed(const std::string& id);
    void reinforcement_intelligence(const std::string& id);
    void Depression(const std::string& id);
    void plain_joy(const std::string& id);
    void crazyness(const std::string& id);
    void anxiety(const std::string& id);
    void recup_compare(const std::string& id);
    void discrimination(const std::string& id);
    void ang_social_conn(const std::string& id);
    void good_social_conn(const std::string& id);
    std::unordered_map<std::string, std::string> modval_to_umap(const std::string& id, int line);
    void w_unmap_model(const std::string& id, std::unordered_map<std::string, std::string> umap, int l);
    
};

#endif //REACTION_H