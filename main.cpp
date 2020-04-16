#include <iostream>
#include "Policy.hpp"
#include "MonteCarlo.hpp"
#include "Game.hpp"

int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(clock()));

    Policy p = Policy(); // initialize random policy
    //p.printPolicy();
    
    MonteCarlo mc;
    Policy p_opt = mc.exploringStartsMC(p);
    
    printf("Learned policy:\n");
    p_opt.printPolicy();
    p_opt.writePolicyToFile("policy");
   
    return 0;
}
