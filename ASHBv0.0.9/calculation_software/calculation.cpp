#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "calculation.h"

// Author Komodo 
// Ici nous faisons tout les calculs que python ne peut pas réaliser 
// pour chaqe nouveaux characters ou chaque modifications de char
// ou de soupe etc ... 


    float Fdesire(float d, int c){
        float n = d + M_E +c;
        return n;
          
    }
    

    float Fbonheur(float c){
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
            float nv = 0.38 * abs(c);
            return nv;
        } else{
            float nv = 0.18 * c;
            return nv;
        }
        
    }

    float Fsolitude(float PreSolitudeStats, float NewValues) {
        //ajuste la stats de solitude
        float new_stats = PreSolitudeStats + NewValues;
        return new_stats;
    }
    



