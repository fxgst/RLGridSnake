#ifndef Utils_hpp
#define Utils_hpp

#define _BOARD_WIDTH        10
#define _BOARD_HEIGHT       10

#define _EATEN_REWARD       1
#define _OUTSIDE_REWARD     -1.0001
#define _STEP_REWARD        0
#define _INF_LOOP_REWARD    -1

#define _EPISODES           10000
#define _GAMMA              0.9

#include <stdio.h>
#include <random>
#include "Enums.cpp"

class Utils {
public:
    static const int BOARD_WIDTH = _BOARD_WIDTH;
    static const int BOARD_HEIGHT = _BOARD_HEIGHT;
    constexpr static const double EATEN_REWARD = _EATEN_REWARD;
    constexpr static const double OUTSIDE_REWARD = _OUTSIDE_REWARD;
    constexpr static const double STEP_REWARD = _STEP_REWARD;
    constexpr static const double INF_LOOP_REWARD = _INF_LOOP_REWARD;
    static const int EPISODES = _EPISODES;
    constexpr static const double GAMMA = _GAMMA;

    int getRandomFromTo(int a, int b);
    double getRandomDoubleFromTo(double a, double b);
    
    Action getActionFromInt(int i);
    int getIntFromAction(Action a);
    std::string getStringFromAction(Action a);
    Action getOppositeAction(Action a);
};

#endif /* Utils_hpp */
