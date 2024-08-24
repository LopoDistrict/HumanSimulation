#pragma once
#include <random>
#include <type_traits>
#include <algorithm>

namespace BetterRand
{   
    using namespace std;
    template<typename T>
    using uniform_distribution_t = std::conditional_t <std::is_floating_point<T>::value, 
            std::uniform_real_distribution<T>, 
            std::conditional_t<std::is_integral<T>::value, 
                std::uniform_int_distribution<T>, 
                void>>;

    struct BERNOULI {};
    struct BINOMIAL {};
    struct POISSON {};
    struct NORMAL {};
    struct UNIFORM {};


    namespace 
    {
        std::random_device rd;
        std::mt19937 gen(rd());
    };

    template<typename D=UNIFORM, typename T>
    T genNrInInterval(T low, T high)
    {
        uniform_distribution_t<T> uniform_dist(low, high);
        return uniform_dist(gen);
    }  

    template<typename D, typename T, 
        typename=enable_if_t<is_same_v<D,BERNOULI>, void>>
    bool genNrInInterval(T probability)
    {
        static_assert(is_same_v<T,float> || is_same_v<T, double>, 
            "Bernouli distrubution needs a probability values as argument !");
        bernoulli_distribution bernouli(probability);
        return bernouli(gen);
    }

    template<typename D, 
        typename=enable_if_t<is_same_v<D,BINOMIAL>, void>>
    typename binomial_distribution<>::result_type genNrInInterval(int nrOfTrials, double probabilityDist)
    {
        binomial_distribution binomial(nrOfTrials, probabilityDist);
        return binomial(gen);
    }

    template<typename D, 
        typename=enable_if_t<is_same_v<D,POISSON>, void>>
    typename poisson_distribution<>::result_type genNrInInterval(double mean)
    {
        poisson_distribution poisson(mean);
        return poisson(gen);
    }

    template<typename D, 
        typename=enable_if_t<is_same_v<D,NORMAL>, void>>
    typename normal_distribution<>::result_type genNrInInterval(double mean = 0.0, double stddev = 1.0)
    {
        normal_distribution normal(mean, stddev);
        return normal(gen);
    }
    

    template<typename T>
    auto getGen(T low, T high)
    {
        return [low, high]() {
             uniform_distribution_t<T> dist(low, high);
             return dist(gen);
        };
    }

    template<typename Container>
    void shuffleContainer(Container& cont)
    {        
        shuffle(cont.begin(), cont.end(), rd);
    }
};