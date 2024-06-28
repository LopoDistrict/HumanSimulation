#include <iostream>
#include <fstream>
//#include <library/dynamic.h>
// #include <library/json.h>
#include <vector>
#include <string>

// Author Komodo 
// Ici nous faisons tout les calculs que python ne peut pas réaliser 
// pour chaqe nouveaux characters ou chaque modifications de char
// ou de soupe etc ... 

int main(){
    std::cout << "calculation of the x day started: "
    // remplacer x par le jour du calcul 
}


int bohneur(PreBohneurStats, NewValues){
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
        return NewValues - (0.038 * abs(c))
    } 
    return NewValues + 0.018 * c
}


int solitude(PreSolitudeStats, NewValues) {
    //ajuste la stats de solitude
    return PreBohneurStats + NewValues
}


