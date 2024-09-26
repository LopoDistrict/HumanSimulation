#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class Cellule{
    public:
        std::string value;
        std::vector<std::string> children;

    void add_child(std::string child){
        children.push_back(child);
    }

    void print_leaf(children){
        if (not children) {
//            std::cout << value << std::endl;
        }else{
            for(int child=0; child < children.size(); child++){
                print_leaf(children);
            }   
        }
    }

    std::vector get_sons(){
        std::vector<std::string> sons;
        for (int child=0; child < children.size(); child++){
            sons.push_back(value)
        }return sons
    }

    

}
