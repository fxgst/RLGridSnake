#ifndef Policy_hpp
#define Policy_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.hpp"

using namespace std;

class Policy {
    
public:
    
    Policy();

    static const int POLICY_HEIGHT = (Utils::BOARD_HEIGHT * 2) - 1;
    static const int POLICY_WIDTH = (Utils::BOARD_WIDTH * 2) - 1;
    static const int POLICY_SIZE = POLICY_HEIGHT * POLICY_WIDTH;
    
    
    Action randomPolicy[POLICY_HEIGHT][POLICY_WIDTH];
    void printPolicy();
    void writePolicyToFile(string filename);
    
private:
    Utils utils;
    
};

#endif /* Policy_hpp */
