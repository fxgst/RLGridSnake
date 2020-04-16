#ifndef MonteCarlo_hpp
#define MonteCarlo_hpp

#include <stdio.h>
#include "Policy.hpp"
#include "Game.hpp"
#include <vector>

class MonteCarlo {
    
public:
    
    Policy exploringStartsMC(Policy p);
    Policy firstVisitMCPredictionStates(Policy p);

private:

    Utils utils;
    double average(std::vector<double> v);
};

#endif /* MonteCarlo_hpp */
