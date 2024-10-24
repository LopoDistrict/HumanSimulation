#include <iostream>
#include <fstream>
#include "calculation_software/calculation.h"
#include <vector>
#include <string>
#include <cmath> 
#include <sstream>
#include "calculation_software/rand.h"
#include <algorithm>
#include "Data.h"
#include <chrono>
#include "calculation_software/include/fast_division.h"
#include <cmath> 
     

//get_value_char + update_csv + get_index
//nv argu = path -> càd que nous devons changer
//dans ce fichier tout les appels de fonctions liées à ces trois méthodes en 
//ajoutant leur path (ou checker si le path est bon car argument constant
//prédefini -> faire une compilation et un run mo 


Data::Data() {
    // Initialize any members if needed
}

// ne pas oublier de creer une lib pour tout ce qui est de roll
// random etc

class Cellule{
    public:
    std::vector<std::string> contenu;
    std::vector<std::string> suivante;

    // Constructor that takes two strings
    Cellule(const std::string& idA, const std::string& idB) {
        contenu.push_back(idA);
        suivante.push_back(idB);
    }
};


    std::string Data::randmId(){
        std::string letters = "abcdefghijklmnopqrstuvwxyz";
        std::string num = "01223456789";
        std::string id;
        for (int i=0; i<8; i++){
            if (i == 0 || i == 6 || i == 7){
                id += num[num_generator(0, 9)];
            }else{
            id += letters[num_generator(0, 25)];
        }
        }
        std::cout << num << std::endl;
        return num;
        
    }


float Data::fastdiv(float quotient, const float& div) { 
    int quotientI = static_cast<int>(round(quotient));
    int divI = static_cast<int>(round(div));  // Calculate at runtime

    std::cout << quotientI << std::endl;

    if ((divI & (divI - 1)) == 0) {  // Check if divI is a power of two
        int log2_divisor = 31 - __builtin_clz(divI);
        return (quotientI >> log2_divisor) * 1.0f;  // Fast divide by power of 2
    }

    uint64_t m = uint64_t(1) << (31 - __builtin_clz(divI) + 32);
    uint64_t c = m / divI;

    return static_cast<float>((c * quotientI) >> (32 + 31 - __builtin_clz(divI)));
}



   void Data::Hygiene(const std::string& id){
        float base_hygiene = stof(get_value_char(id, 10));
            if (get_model(id, 1) != "disease=null"){
                //malade
                base_hygiene -= 2.15 * (get_neighbour(id).size() * 1.0);
            }else{
                base_hygiene += 4.86;
            }
        update_csv_cell(get_index(id), 10, std::to_string(base_hygiene));
   }

   void Data::start_desire(const std::string& id) {
    //Data obj; // Assuming Data is a defined class
    std::cout << "tool function : start_desire()" << std::endl;
    std::string gender = get_value_char(id, 11); // Get the character directly
    
    std::ifstream mailleFile("./data/temp/presence.asb");
    std::vector<std::string> maille;
    std::string line;

    // Read lines from the file into the maille vector
    while (std::getline(mailleFile, line)) {
        maille.push_back(line);
    }
    //print_vector(maille); // Assuming print_vector is a defined method

    // Check if the id exists in maille
    for (int i = 0; i < maille.size(); ++i) {
        std::cout << maille[i].substr(1, 7) << std::endl;
        if (maille[i].substr(1, 7).find(id)) {
            // Convert maille[i][j] (a char) to string
            std::string current_id(maille[i].substr(9, 8)); // Create a string from the character
            std::cout << "current_id: " << current_id << std::endl;

            if (get_value_char(current_id, 11) != gender) {
                // Determine if idA starts desiring idB in its maille
                std::vector<std::string> lpoint = get_point_list(id);
                std::vector<std::string> lc = get_couple_list(id);

                if (roll_random(94, 0, 250) && 
                    (std::find(lpoint.begin(), lpoint.end(), current_id) == lpoint.end()) &&
                    (std::find(lc.begin(), lc.end(), current_id) == lc.end())) {    
                    
                    std::cout << "Desire started: " << id << std::endl;

                    // Start a real attraction, so we remember the pointer
                    std::ofstream mem_file("./data/memory/couple.mem", std::ios::app);
                    mem_file << id << ">" << current_id << "0" << num_generator(2, 7) << std::endl;
                    write_main_logs("Desire_created" + id + ">" + current_id);
                    update_csv_cell(get_index(id), 13, "yes"); // Update CSV cell
                }
            }
        }
    }
}    


/*
void Data::eraseFileLine(std::string path, std::string erased_line, int l) {
    
    //prend en argument un nom de ligne specifique ex: id=47896 ou un numero de ligne
    std::string line;
    std::ifstream fin;
    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");
    int c_temp = 0;
    while (getline(fin, line)) {
        //si le premier est faux alors c'est un num de ligne et pas ligne specifique
        temp << line << std::endl;
        c_temp ++;
    }

    temp.close();
    fin.close();
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}*/

void Data::eraseFileLine(std::string path, std::string erased_line, int l){
    //si line = null sonc c'est une ligne - l null 00
    std::ifstream file(path);
    std::vector<std::string> lines;
    std::string line;
    int c_temp = 0;
    while (std::getline(file, line)) {
        if(c_temp != l && erased_line != line){
            lines.push_back(line);
        }
        c_temp+=1;
        
    }
    file.close();
    /*
    // Check if the line number is valid
    if (line_number < 1 || line_number > lines.size()) {
        std::cout << "Error: Line number out of range." << std::endl;
        return;
    }*/

    // Append the value to the specified line

    // Write the modified contents back to the file
    std::ofstream out_file(path);
    for (const auto& l : lines) {
        out_file << l << std::endl;
    }
    out_file.close();
}


void Data::app_l(const std::string& file_path, int line_number, const std::string& value) {
    // ajoute une valeur a une ligne a un fichier
    std::ifstream file(file_path);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Check if the line number is valid
    if (line_number < 1 || line_number > lines.size()) {
        std::cout << "Error: Line number out of range." << std::endl;
        return;
    }

    // Append the value to the specified line
    lines[line_number - 1] = value;

    // Write the modified contents back to the file
    std::ofstream out_file(file_path);
    for (const auto& l : lines) {
        out_file << l << std::endl;
    }
    out_file.close();
}


    void Data::start_couple(const std::string& idA, const std::string& idB) {
        // Combine the values and convert to float
        float average = stof((get_value_char(idA, 1) + get_value_char(idB, 1))) / 2.0;
        if (average >= 17) { 
            std::string tree_parent = "TreeNode('X', TreeNode([" + idA + ", " + idB + "], []))";
            std::ofstream file_gen("./data/memory/gen.mem", std::ios::app);  // Use double quotes for string literals
            file_gen << tree_parent << std::endl;
            desire(idA, 4.0, true);
            desire(idB, 4.0, true);
            bonheur(idA, 7.0);  // Note: Changed from bohneur to bonheur
            bonheur(idB, 7.0);
            std::cout << "new couple" << idA << "  " << idB << std::endl;
            std::cout << tree_parent << std::endl;
            write_main_logs("couple:" + idA + " : " + idB );
        } else {
            std::cout << "Error: not tall enough" << std::endl;
        }
        std::ofstream couple("./data/memory/couple.mem", std::ios::app);
        couple << idA << "-" << idB << stoi(get_desire_single(idA, idB)) + num_generator(4, 9) << std::endl;

        std::ifstream file("./data/memory/couple.mem");
        std::string line;
        while (std::getline(file, line)) {
            if (line.substr(0, 8) + '>' + line.substr(9, 8) == idA + ">" + idB
                || line.substr(0, 8) + '>' + line.substr(9, 8) == idB + ">" + idA) {
                
                eraseFileLine("./data/memory/couple.mem", line, 00);
                //on rmeove la line ou il flirt
            }
        }
        
        //designe qu'un couple est maintenant un couple
        //doit enlever la ligne de pointeur

}

std::string Data::point(const std::string& id) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 8) == id && line[8] == '>') {
            return line.substr(9, 8);
        }
    }
    return "not";
}

std::vector<std::string> Data::get_point_list(const std::string& id) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    std::vector<std::string> point_list;
    while (std::getline(file, line)) {
        if (line.substr(0, 8) == id && line[8] == '>') {
            point_list.push_back(line.substr(9, 8));
        }

    }
    return point_list;
}

std::string Data::get_couple(const std::string& id) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 8) == id && line[8] == '-') {
            return line.substr(9, 8);
        }
    }
    return "not";
}

std::vector<std::string> Data::get_couple_list(const std::string& id) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    std::vector<std::string> couples;
    while (std::getline(file, line)) {
        if (line.substr(0, 8) == id && line[8] == '-') {
            couples.push_back(line.substr(9, 8));
            
        }
    }
    return couples;
}

void Data::modify_desire(const std::string& idA, const std::string& idB, const std::string& constant) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        
        if (line.substr(0, 17) == idA + "-" + idB || line.substr(0, 17) == idA + ">" + idB) {
            line = idA + line[8] + idB + std::to_string(stoi(constant) + stoi(line.substr(17, line.size()-17)));;
            //incroyabklement compliqué pour rien au final 
            break;
        } else if (line.substr(0, 17) == idB + ">" + idA || line.substr(0, 17) == idB + "-" + idA) {
            line = idB + line[8] + idA + std::to_string(stoi(constant) + stoi(line.substr(17, line.size()-17)));
            break;
        }
        lines.push_back(line);
    }

    std::ofstream outFile("./data/memory/couple.mem");
    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
}

std::string Data::get_desire_couple(const std::string& idA, const std::string& idB) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(idA) != std::string::npos && line.find(idB) != std::string::npos) {
            return line.substr(17);
        }
    }
    return "";
}

std::string Data::get_desire_single(const std::string& idA, const std::string& idB) {
    std::ifstream file("./data/memory/couple.mem");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 17) == idA + ">" + idB) {
            return line.substr(17);
        }
    }
    return "";
}

    void Data::desire(const std::string& id, float constant, bool alr){
        //alr: si deja un couple -> n'a pas besoin de tester si doit
        //start_couple
        std::vector<std::string> point_lst = get_point_list(id);
        
        for(int i = 0 ; i<point_lst.size() ;i++){

            std::string idB = point_lst[i];
            if (!alr  && idB != "not"){
                //le desir est reciproque donc on test si il ont desir haut
                int sum_desire = stoi(get_desire_single(id, idB) + get_desire_single(idB, id));
                if(roll_random(sum_desire, 70, 200)){
                    //le desire a marché donc on start un couple
                    start_couple(id, idB);
                } else {
                    //modify_desire(id, idB, std::to_string(sum_desire 3)); ==
                    modify_desire(id, idB, std::to_string(fast_division::divide32<3>::quotient(sum_desire)));
                    //ici le test n'as pas marché mais on continue d'augmenter le desir
                }
            }
            modify_desire(id, idB, std::to_string(num_generator(6, 11) + constant));
            //bonheur peut faire baisser un desir
        }
    }

    void Data::write_logs(const std::string& val) {
        //write every types of logs -> more for debug
        std::ofstream logsFile("./data/logs/logs.txt", std::ios::app);
        if (logsFile.is_open()) {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            logsFile << "<" << std::ctime(&now_c) << "> " << val << "\n";
        }
    }

    void Data::write_main_logs(const std::string& val) {
        //write importants logs
        std::ofstream logsFile("./data/logs/main_logs.txt", std::ios::app);
        if (logsFile.is_open()) {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            logsFile << "<" << std::ctime(&now_c) << "> " << val << "\n";
        }
    }



    bool Data::procreation(const std::string& id, float const_breeding){
        //a finir avec la nv methode de procreation
        //while prend tout les couples une personnes peut procréer 
        //plusieurs fois
        std::ifstream couple("./data/memory/couple.mem");
        std::string line;
        while(std::getline(couple, line)){
            if(id.find(line) != std::string::npos){
                //found
                std::string second_id = line.substr(8, 16);
                if (stoi(get_desire_couple(id, second_id)) + num_generator(0, 25) >= 65){
                    //ils ont un taux de désir assez pour procréer
                    if (roll_random(140+const_breeding, 0, 200) == true){
                        //la procreation a reussi
                        desire(id, 7.0, true);
                        write_logs("Proreation sucess" + line.substr(8,16));
                        write_main_logs("Proreation sucess" + line.substr(8,16));
                        return true;
                    }else{
                        return false;
                    }

                }
            }
        }
        return false;
    }


    void Data::solitude(const std::string& id) {
        // Update solitude stats in the file based on presence
        std::cout << "tool function definition: Data::solitude" << std::endl;
        std::ifstream mailleFile("./data/temp/presence.asb");
        if (!mailleFile.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }

        std::vector<std::string> maille;
        std::string line;

        // Read all lines into a vector
        while (std::getline(mailleFile, line)) {
            maille.push_back(line);
        }
        print_vector(maille);
        mailleFile.close();

        
        float old = stof(get_value_char(id, 7));
        //float new_value = (stoi(get_value_char(id, 3)) / 9) / (stoi(get_value_char(id, 8)) / 6); == 
        //float new_value = fast_division::divide32<fast_division::divide32<9>::quotient(stoi(get_value_char(id, 3)))>::
        //quotient(fast_division::divide32<6>::quotient(stoi(get_value_char(id, 8))));

        float new_value = fastdiv(fastdiv((stoi(get_value_char(id, 3))), 9), fastdiv(stoi(get_value_char(id, 8)), 6));
        
        
        float nvstats;
        if (std::find(maille.begin(), maille.end(), id) == maille.end()) {
            nvstats = Fsolitude(old, new_value);
            std::cout << "ID not in presence data" << std::endl;
        } else {
            int count_id = std::count(maille.begin(), maille.end(), id);
            //nvstats = Fsolitude(old, new_value / count_id); ==
            //nvstats = Fsolitude(old, fast_division::divide32<count_id>::quotient(new_value));
            nvstats = Fsolitude(old, fastdiv(new_value, count_id));
        }

        std::cout << "New solitude stats: " << std::ceil(nvstats) << std::endl;
        int ind = get_index(id);
        std::cout << "Index of ID: " << ind << std::endl;
        update_csv_cell(ind, 7, std::to_string(std::ceil(nvstats)));
    }


// Doit refaire cette fonction en voyant avec start_desire 
// elle est actuellement totalement fausse et doit être refaite depuis le debut
// :) 
/*
    void desire(const std::string& id ,bool alr=false){
        std::cout << id << std::endl;
        float old_s = stof(get_value_char(id, 6));
        
        if (old_s >= 50 && not alr){
            double (std::string id, bool alr = false) {
            std::ifstream pointer("./data/memory/couple.mem");
            std::string line;
            while (std::getline(pointer, line)) {
                Cellule* linked = new Cellule(line);
                if (linked->contenu == id) {
                    std::getline(pointer, line);
                    Cellule* pointed = new Cellule(line);
                    double formula = (150 + get_value_char(pointed->contenu, 3));
                    if (roll_random(formula / (old_s / 5), 0, 200) || roll_random(formula / (desire(old_s, 0) / 5), 0, 200)) {
                        return start_couple(id, pointed->contenu);
                    } else {
                        std::ofstream f("target.txt", std::ios::in | std::ios::out);
                        std::string line;
                        while (std::getline(f, line)) {
                            if (line != std::to_string(reinterpret_cast<long long>(new Cellule(id, pointed->contenu)))) {
                                f << line << std::endl;
                                std::cout << line << std::endl;
                            }
                        }
                        f.close();
                    }
                }
            }
            pointer.close();

        double nvstats = desire(old_s, 0);
        return update_csv_cell(get_index(id), 6, std::ceil(nvstats));
    
        } 
   }
*/

   int Data::get_index(const std::string& id, std::string path) {
        std::cout << "tool function definition: get_index" << std::endl;

        std::ifstream file(path);
        std::string line;
        int num = 0;
        while (getline(file, line)) {
            num++;
            std::vector<std::string> row;
            std::string word;
            std::stringstream ss(line);
            while (getline(ss, word, ',')) {
                row.push_back(word);
            }
            if (row[0] == id) {
                std::cout << num-1 << std::endl;
                return num - 1;
            }
        }

        return -1;
    }

    std::string Data::get_value_char(const std::string& id, int value_ind, std::string path) {
        std::cout << "tool function definition: get_value_char" << std::endl;
        std::ifstream file(path);
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> row;
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ',')) {
                row.push_back(word);
            }
            if (row[0] == id) {
                std::cout << row[value_ind] << std::endl;
                return row[value_ind];
            }
        }
        return "Error: bad id/value";
    }

/*
std::string get_value_char(const std::string& id, int ind, const std::string& path) {
    std::ifstream file(path);
    std::string result;
    std::string line;

    while (std::getline(file, line)) {
        if (line.find(id) != std::string::npos) {
            size_t pos = 0;
            int count = 0;
            while ((pos = line.find(',')) != std::string::npos) {
                if (count == ind) {
                    return line.substr(0, pos);
                }
                line.erase(0, pos + 1);
                count++;
            }
            if (count == ind) {
                return line; // return the last element if it's the one we want
            }
        }
    }
    return ""; // return empty string if not found
}
*/
    std::string Data::get_position(const std::string& id, int value_ind) {
    std::ifstream file("./data/TempChar.csv");
    
    //if (!file.is_open()) {
    //    return "Error: could not open file";
    //}

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;
        
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (row[0] == id) {
            file.clear();  // clear the error state of the stream
            file.seekg(0); // reset the file pointer to the beginning
            return row[value_ind];
        }
    }

    return "Error: bad id/value";
}


    // Function to evaluate a string and return a vector of vector of floats
    std::vector<std::vector<float>> Data::eval(const std::string& str) {
        std::cout << "tool function definition: eval (matrix)" << std::endl;
        std::cout << str << std::endl;

        std::vector<std::vector<float>> result;
        std::istringstream stream(str);
        std::string line;

        while (std::getline(stream, line)) {
            std::istringstream line_stream(line);
            std::vector<float> values;
            float value;
            
            while (line_stream >> value) {
                values.push_back(value);
            }
            
            if (!values.empty()) {
                result.push_back(values);
            }
        }
        
        return result;
    }


    float Data::Fbonheur(float c){
        std::cout << "entering function"<< std::endl;
        // calcul le bohneur en fonction du precedent
        // calcul le bohneur à partir de 2 valeur 
        // c : constante qui peut affecter le bohneur 
        //       - négativement si c <= 0
        //       - positivement si c > 0
        //       - nullement si c = 0
        // v : valeur du bohneur au t-1, donc la valeur du bohneur au
        // nouveau jour
        // le bohneur baisse plus lentement qu'il croit
        
        if (c <= 0){
            float nv = 0.402 * c;
            std::cout << "calculation.cpp -nv" << nv << std::endl;
            return nv;
        } else{
            float nv = 0.223 * c;
            std::cout << "calculation.cpp nv" << nv << std::endl;
            return nv;
        }
            
        }




   void Data::bonheur(const std::string& id, float constant) {
    float old_s = std::stof(get_value_char(id, 3));  // Ensure this returns a string representation of a float
    std::cout << id << std::endl;
    std::cout << "constant" << constant << std::endl;
    std::ifstream maille("./data/temp/presence.asb");
    std::vector<std::string> maille2;
    print_vector(maille2);
    std::string line;
    float nvstats;

    while (std::getline(maille, line)) {
        maille2.push_back(line);
    }

    // Check if id is in maille2
    if (std::find(maille2.begin(), maille2.end(), id) == maille2.end()) {
        std::cout << "not in mesh" << std::endl;
        constant -= 0.2;
        nvstats = old_s + Fbonheur(constant);
        std::cout << "nvstats bonheur: " << nvstats << std::endl;
    } else {
        std::cout << "in mesh" << std::endl;
        constant += num_generator(1, 4);

        std::ifstream file("./data/temp/presence.asb");
        std::string presence_data_str;
        std::getline(file, presence_data_str);
        std::vector<std::vector<float>> presence_data = eval(presence_data_str);

        std::vector<std::vector<float>> result;

        // Find neighbors in the presence_data
        for (const auto& id_list : presence_data) {
            if (std::find(id_list.begin(), id_list.end(), std::stof(id)) != id_list.end()) {
                result.push_back(id_list);
            }
        }

        for (const auto& id_list : result) {
            for (float i : id_list) {
                std::cout << i << std::endl;
                // Ensure that you are using the correct conversion
                if (std::to_string(i) != id && std::stoi(get_value_char(std::to_string(i), 3)) >= 60) {
                    std::cout << "good" << std::endl;
                    constant += num_generator(4, 8);
                }
            }
        }

        nvstats = old_s + Fbonheur(constant);
        std::cout << "nvstats bonheur: " << nvstats << std::endl;
    }

     update_csv_cell(get_index(id), 3, std::to_string(nvstats));
}





    bool Data::age_update(const std::string& id, int day){ // 365 jours == trop long
        // nouvelle année toute les 30 jours (valeurs a faire varier)
        std::cout << id << std::endl;
        std::cout << day << std::endl;
        std::string current_age = get_value_char(id, 12);
        std::cout << current_age << std::endl;
        if (stoi(current_age) * 20 + stoi(get_value_char(id, 1)) >= stoi(current_age) * 20 + day){
            return true;
        }
        return false;
    }

    void Data::stress(const std::string& id, int constant){
        std::cout << id << std::endl;
        std::cout <<  constant << std::endl;

        // Sn+1 = (bonheur/santé_mentale + const) * 1.21;
        // augmente rapidement quand la constante est grande
        // constante definie par les maladies 
        float bonheur = stof(get_value_char(id, 3));
        //float nvstats = (bonheur / stof(get_value_char(id, 5)) + constant) * 1.21; 
        //float nvstats = (fast_division::divide32<stof(get_value_char(id, 5))>::quotient(bonheur) + constant) * 1.21; 
        float nvstats = (fastdiv(bonheur, stof(get_value_char(id, 5))) + constant) *  1.21;

        std::cout <<  bonheur << std::endl;         
        std::cout <<   nvstats << std::endl;
        update_csv_cell(get_index(id), 4, std::to_string(std::ceil(nvstats)));
    }
    
    void Data::health(const std::string& id, float constant){
        std::cout << id << std::endl;
        std::cout << constant << std::endl;
        //const maladie + emotion
        // + age (+le char est vieux + il est perd en health)
        if (stoi(get_value_char(id, 1)) >= 50){
            update_csv_cell(get_index(id), 2, std::to_string(stoi(get_value_char(id, 2)) + constant));            
        }
        update_csv_cell(get_index(id), 2, std::to_string(stof(get_value_char(id, 2)) + constant));
    }

    void Data::print_vector(const std::vector<std::string>& vec) {
        std::cout << "tool function definition: print_vector" << std::endl;
        
    if (vec.empty()) {
        std::cout << "The vector is empty." << std::endl;
        return;
    }

    std::cout << "Vector contents: { ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;
}

std::vector<std::string> Data::get_neighbour(const std::string& id) {
    std::cout << "tool function definition: get_neighbour" << std::endl;
    std::ifstream file("./data/temp/presence.asb");
    std::string line;
    std::vector<std::string> result;

    // Check if the file is open
    //if (!file.is_open() && !file) {
    //    std::cerr << "Error opening the file!" << std::endl;
    //    return {};
    //}

    // Read each line from the file
    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        std::string current_id;
        std::vector<std::string> ids;

        // Read all IDs from the current line
        while (line_stream >> current_id) {
            ids.push_back(current_id);
        }

        // Check if the given id is in the current line
        if (std::find(ids.begin(), ids.end(), id) != ids.end()) {
            // If found, add all IDs from this line to the result
            for (const auto& neighbour_id : ids) {
                if (neighbour_id != id) { // Exclude the original id
                    result.push_back(neighbour_id);
                }
            }
        }
    }

    return result;
}

    
    std::string Data::get_model(const std::string& id, int line) {
        std::cout << "tool function definition: get_model" << std::endl;
        std::cout << id << std::endl;
        std::cout << line << std::endl;

        std::ifstream file("./data/memory/model" + id + ".dmem");
        std::string result;
        if (file.is_open()) {
            for (int i = 0; i <= line; ++i) {
                std::getline(file, result);
            }
            file.close();
        }
        return result;
    }


    bool Data::disease(const std::string& id){
        std::cout << "tool function disease" << std::endl;
        //  ??? possibilité d'une constante => si une pop/char a deja été 
        //contaminée donc elle est moins a risque de se faire contaminée        
        //on check si des personne on déja des disease autour de lui
        std::vector<std::string> neighbour = get_neighbour(id); 
        double multiplicator_contaminated = neighbour.size();  

        for (int i=0; i < neighbour.size(); i++){
            if (get_model(id, 1) != "disease=null"){
                multiplicator_contaminated *= 3.2;
            }else{
                multiplicator_contaminated *= 0.93;
            }    
        }   
        std::cout << "multiplicator contamination" << multiplicator_contaminated << std::endl;
        return roll_random(200-multiplicator_contaminated, 0, 800);
        // a checker pour roll
    }
    

    void Data::mentalhealth(const std::string& id, float constant){
        std::cout << id << std::endl;
        std::cout << constant << std::endl;
        // constante definie par les maladies 
        //et par la santé en générale
        //aussi par l'age quand age >= 70 const+= age/15
        //ou par emotion
        float base = stof(get_value_char(id, 5));
        std::ifstream maille("./data/temp/presence.asb");
        std::vector<std::string> maille2;
        std::string line;
        while (std::getline(maille, line)) {
            maille2.push_back(line);
        }

        if (std::find(maille2.begin(), maille2.end(), id) == maille2.end()) {
            std::cout << "not in mesh" << std::endl;
            update_csv_cell(get_index(id), 5, std::to_string(base -= 1.4 + constant));  
        } else {
            std::cout << "in mesh" << std::endl;
            update_csv_cell(get_index(id), 5, std::to_string(base -= 0.2 + constant));
        }
    }


    void Data::update_csv_cell(int row_index, int col_index, const std::string& new_value, std::string path) {
        std::cout << "tool function definition: update_csv_cell" << std::endl;
        std::cout << row_index << std::endl;
        std::cout << col_index << std::endl;
        std::cout << new_value << std::endl;
        // Read the CSV file
        std::ifstream file(path);
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
        std::ofstream out_file(path);
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

/*
int main(){
    Data obj;
    obj.bonheur("1cxsns07", 0);
    std::cout << var << std::endl;
    obj.bonheur("1cxsns07", 5);
    std::cout << var << std::endl;
    obj.bonheur("1cxsns07", -5);
    std::cout << var << std::endl;
    obj.bonheur("1cxsns07", 10);
    std::cout << var << std::endl;
    obj.bonheur("1cxsns07", -10);
    std::cout << var << std::endl;
}*/