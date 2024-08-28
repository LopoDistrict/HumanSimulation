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

   void Data::Hygiene(const std::string& id){
        float base_hygiene = stof(get_value_char(id, 10));
            if (get_model(id, 1) != "disease=null"){
                //malade
                base_hygiene -= 3.35 * (get_neighbour(id).size() * 1.0);
            }else{
                base_hygiene += 2.86;
            }
        update_csv_cell(get_index(id), 10, std::to_string(base_hygiene));
   }

    void Data::start_desire(const std::string& id) {
    // Horrible function construction with: 2, if: 4, for: 2
    std::string gender = get_value_char(id, 11); // Changed to get the character directly
    std::ifstream mailleFile("./data/temp/presence.asb");
    std::vector<std::string> maille;
    std::string line;

    // Read lines from the file into the maille vector
    while (std::getline(mailleFile, line)) {
        maille.push_back(line);
    }
    print_vector(maille);

    // Check if the id exists in maille
    if (std::find(maille.begin(), maille.end(), id) != maille.end()) {
        for (size_t i = 0; i < maille.size(); ++i) {
            if (maille[i] == id) {
                for (size_t j = 0; j < maille[i].size(); ++j) {
                    // Convert maille[i][j] (a char) to string
                    std::string current_id(1, maille[i][j]); // Create a string from the character
                    std::cout << "current_id" << current_id << std::endl;

                    if (get_value_char(current_id, 11) != gender) {
                        // Determine if idA starts desiring idB in its maille
                        if (roll_random(40, 0, 200)) { // Simplified condition
                            std::cout << "desire started: " << id << std::endl;
                            std::cout << maille[i][j] << std::endl;
                            // Start a real attraction, so we remember the pointer
                            std::ofstream mem_file("./data/memory/couple.mem", std::ios::app);
                            // If the attraction worked, point idA to char idB (maille[i][j])
                            //Cellule(id, current_id); // Call Cellule with correct parameters
                            mem_file << id << ">" << current_id << num_generator(2, 7) << std::endl;
                            update_csv_cell(get_index(id), 13, "yes"); //on change mtn il est en couplle
                            //num_generator est le desir lorsqu'il est créer
                            //le desir varie selon certaine personne
                            //c'est pour cela qu'il ne peut pas être fixe
                            //ex: 0rbveqy0j0i>5ihdbpa0a4k25

                            //id pointe vers current_id
                            //id>current_id
                        }
                    }
                }
            }
        }
    }
}

void eraseFileLine(std::string path, std::string eraseLine) {
    std::string line;
    std::ifstream fin;
    
    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) {
        // write all lines to temp other than the line marked for erasing
        if (line != eraseLine)
            temp << line << std::endl;
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

    void Data::start_couple(const std::string& idA, const std::string& idB) {
        // Combine the values and convert to float
        float average = stof((get_value_char(idA, 1) + get_value_char(idB, 1))) / 2.0;
        if (average >= 16) {
            std::string tree_parent = "TreeNode('X', TreeNode([" + idA + ", " + idB + "], []))";
            std::ofstream file_gen("./data/memory/gen.mem", std::ios::app);  // Use double quotes for string literals
            file_gen << tree_parent << std::endl;
            desire(idA, 4.0, true);
            desire(idB, 4.0, true);
            bonheur(idA, 8.0);  // Note: Changed from bohneur to bonheur
            bonheur(idB, 8.0);
            std::cout << "new couple" << idA << "  " << idB << std::endl;
            std::cout << tree_parent << std::endl;
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
                
                eraseFileLine("./data/memory/couple.mem", line);
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
        if (line.substr(0, 17) == idA + "-" + idB || line.substr(0, 17) == idB + "-" + idA) {
            line += constant;
        } else if (line.substr(0, 17) == idA + ">" + idB || line.substr(0, 17) == idB + ">" + idA) {
            line += constant;
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
        std::string idB = point(id);
        if (!alr && idB != "not"){
            //le desir est reciproque donc on test si il ont desir haut
            int sum_desire = stoi(get_desire_single(id, idB) + get_desire_single(idB, id));
            if(roll_random(sum_desire, 80, 200)){
                //le desire a marché donc on start un couple
                start_couple(id, idB);
            } else {
                modify_desire(id, idB, std::to_string(sum_desire/4));
                //ici le test n'as pas marché mais on continue d'augmenter le desir
            }
        }
        modify_desire(id, idB, std::to_string(num_generator(1, 4) + constant));
        //bonheur peut faire baisser un desir

    }


    bool Data::procreation(const std::string& id){
        //a finir avec la nv methode de procreation
        std::ifstream couple("./data/memory/couple.mem");
        std::string line;
        while(std::getline(couple, line)){
            if(id.find(line) != std::string::npos){
                //found
                std::string second_id = line.substr(8, 16);
                if (stoi(get_desire_couple(id, second_id)) + num_generator(0, 25) >= 65){
                    //ils ont un taux de désir assez pour procréer
                    if (roll_random(140, 0, 200) == true){
                        //la procreation a reussi
                        desire(id, 7.0, true);
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
        float new_value = (stoi(get_value_char(id, 3)) / 9) / (stoi(get_value_char(id, 8)) / 6);

        std::cout << "Old solitude value: " << old << std::endl;
        std::cout << "New solitude value: " << new_value << std::endl;

        float nvstats;
        if (std::find(maille.begin(), maille.end(), id) == maille.end()) {
            nvstats = Fsolitude(old, new_value);
            std::cout << "ID not in presence data" << std::endl;
        } else {
            int count_id = std::count(maille.begin(), maille.end(), id);
            nvstats = Fsolitude(old, new_value / count_id);
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
        std::cout << id << std::endl;
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
        std::cout << id << std::endl;
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
        constant += 3;

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
                    constant += 6.5;
                }
            }
        }

        nvstats = old_s + Fbonheur(constant);
        std::cout << "nvstats bonheur: " << nvstats << std::endl;
    }

     update_csv_cell(get_index(id), 3, std::to_string(std::ceil(nvstats)));
}


    bool Data::age_update(const std::string& id, int day){
        std::cout << id << std::endl;
        std::cout << day << std::endl;
        std::string current_age = get_value_char(id, 12);
        std::cout << current_age << std::endl;
        if (stoi(current_age) * 365 + stoi(get_value_char(id, 1)) >= stoi(current_age) * 365 + day){
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
        float nvstats = (bonheur / stof(get_value_char(id, 5)) + constant) * 1.21;   

        std::cout <<  bonheur << std::endl;         
        std::cout <<   nvstats << std::endl;
        update_csv_cell(get_index(id), 4, std::to_string(std::ceil(nvstats)));
    }
    
    void Data::health(const std::string& id, float constant){
        std::cout << id << std::endl;
        std::cout << constant << std::endl;
        //const maladie + emotion
        // + age (+le char est vieux + il est perd en health)
        if (stoi(get_value_char(id, 5)) <= 50){
            update_csv_cell(get_index(id), 5, std::to_string(stoi(get_value_char(id, 2)) - 2.0 + constant));            
        }
        update_csv_cell(get_index(id), 5, std::to_string(stof(get_value_char(id, 2)) + constant));
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
            std::cout << ", "; // Add a comma between elements
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
        std::cout << id << std::endl;
        //  ??? possibilité d'une constante => si une pop/char a deja été 
        //contaminée donc elle est moins a risque de se faire contaminée        
        //on check si des personne on déja des disease autour de lui
        std::vector<std::string> neighbour = get_neighbour(id); 
        double multiplicator_contaminated = neighbour.size();  

        for (int i=0; i < neighbour.size(); i++){
            if (get_model(id, 1) != "disease=null"){
                multiplicator_contaminated *= 8.4;
            }else{
                multiplicator_contaminated *= 0.8;
            }    
        }   
        std::cout << "multiplicator contamination" << multiplicator_contaminated << std::endl;
        return roll_random(0, 200-multiplicator_contaminated, 400);
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

