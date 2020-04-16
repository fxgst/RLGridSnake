#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Policy.hpp"
#include "Utils.hpp"
#include "Step.cpp"
#include <vector>

class Game {
    
public:
    Game(); // initializes random board

    Action getActionFromPolicy(Policy p);
    void printBoard();
    void printEpisode(std::vector<Step> episode);
    double calculateReward(int count);
    std::vector<Step> generateEpisode(Policy p);
    void performAction(Action action);
    
private:
    Utils utils;
    int x_apple, y_apple, x_snake, y_snake, x_distance, y_distance;
    
};
#endif /* Game_hpp */
