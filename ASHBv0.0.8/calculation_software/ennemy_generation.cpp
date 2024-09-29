#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>



std::string LatPlayer = "";
std::string LongPlayer = "";

double doubleRand(std::default_random_engine& generator) {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

    // le script couvre d'abord le fichier des posi player 
    //ensuite il essaye de chercher si dans les coord il y a un - ou une coord == un chiffre
    // ex -3. ou -0 ou -21 ou 9

int main() {
    
    std::remove("ennemy.txt");
     std::ifstream playerPosition("player_position.txt");

    if (!playerPosition.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(playerPosition, line)) {
        size_t semicolonPos = line.find(';');
        if (semicolonPos != std::string::npos) {
            std::string LatPlayer = line.substr(0, 5);
            std::string LongPlayer = line.substr(semicolonPos + 1, 5);

            if (line.find('-') != std::string::npos || line.find('.') != std::string::npos) {
                if (line[0] == '-') {
                    LatPlayer = line.substr(0, 6);
                }

                if (line[0] == '.' || line[1] == '.') {
                    LatPlayer = line.substr(0, 4);
                }

                if (line[semicolonPos + 1] == '-') {
                    LongPlayer = line.substr(semicolonPos + 1, 4);
                }

                if (line[semicolonPos + 1] == '.' || line[semicolonPos + 2] == '.') {
                    LongPlayer = line.substr(semicolonPos + 1, 4);
                }
            }
            std::vector<std::string> enemies = {"Project MKA1","raider","cannibal", "immoral butchers", "cultist", "starving waste lander", "tavelling salesman"};
            std::cout << LatPlayer << std::endl;
            std::cout << LongPlayer << std::endl;

            std::cout << "start" << std::endl;
            std::remove("ennemy_location.txt");
            std::remove("ennemies_location.lhhd");

            std::ofstream file("ennemies_location.lhhd", std::ios::app);
            if (file.is_open()) {
                for (int x = 0; x < 18; x++) {
                    std::cout <<  "" << std::endl;
                    std::random_device rd;
                    std::default_random_engine generator(rd());
                    std::cout <<  "new line" << std::endl;
                    std::cout << "latitude: "<< LatPlayer << " longitude: " << LongPlayer << std::endl;
                    std::cout << "latitude: " << LatPlayer + std::to_string(doubleRand(generator)).substr(2) << " longitude: " << LongPlayer + std::to_string(doubleRand(generator)).substr(2) << std::endl;

                    file << LatPlayer + std::to_string(doubleRand(generator)).substr(2) << ";" << LongPlayer + std::to_string(doubleRand(generator)).substr(2) << ";" << enemies[std::rand() % enemies.size()] << ";" << std::endl;
                }
                }
                    
        
            file.close();
            playerPosition.close();
        }
    }
    std::cout << "process finished" << std::endl;
    return 0;
    }
