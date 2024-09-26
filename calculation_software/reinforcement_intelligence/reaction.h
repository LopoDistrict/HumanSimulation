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



class reaction {
public:
    reaction();
    void get_last_line(const std::string& path);
    std::string get_value_csv(int l, int value_ind, std::string path);
    void murder(const std::string& id);
    void suicide(const std::string& id );
    void desire(const std::string& id);
    void breeding(const std::string& id);
    int get_old_stats(const std::string& id, int value);
    std::string get_current_action(const std::string& id);
    float result_RI(const std::string& id, float prec_stats, int ind, int mult_const);
    bool is_sup_attended(const std::string& id);
    void get_value_choosed(const std::string& id);
    void reinforcement_intelligence(const std::string& id);
    void Depression(const std::string& id);
    void plain_joy(const std::string& id);
    void crazyness(const std::string& id);
    void anxiety(const std::string& id);
};

#endif //REACTION_H