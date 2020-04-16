#include "Utils.hpp"

using namespace std;

int Utils::getRandomFromTo(int a, int b) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(a,b); // distribution in range [a, b]
    return dist(rng);
}

double Utils::getRandomDoubleFromTo(double a, double b) {
    return (b-a) * ( (double)rand() / (double)RAND_MAX ) + a;
}

int Utils::getIntFromAction(Action a) {
    switch (a) {
        case Up:
            return 0;
        case Down:
            return 1;
        case Left:
            return 2;
        case Right:
            return 3;
        default:
            return 0;
    }
}

string Utils::getStringFromAction(Action a) {
    switch (a) {
        case Up:
            return "U";
        case Down:
            return "D";
        case Left:
            return "L";
        case Right:
            return "R";
        default:
            return "U";
    }
}

Action Utils::getActionFromInt(int i) {
    switch (i) {
        case 0:
            return Up;
        case 1:
            return Down;
        case 2:
            return Left;
        case 3:
            return Right;
        default:
            printf("Error get action from int\n");
            return Up;
    }
}

Action Utils::getOppositeAction(Action a) {
    switch (a) {
        case Up:
            return Down;
        case Down:
            return Up;
        case Left:
            return Right;
        case Right:
            return Left;
        default:
            printf("Error get opposite action\n");
            return Down;
    }
}
