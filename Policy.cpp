#include "Policy.hpp"

using namespace std;

Policy::Policy() {
    for (int x = 0; x<POLICY_WIDTH; x++) {
        for (int y = 0; y<POLICY_HEIGHT; y++) {
            randomPolicy[x][y] = utils.getActionFromInt(utils.getRandomFromTo(0, 3));
        }
    }
}

void Policy::printPolicy() {
    for (int x = 0; x<POLICY_WIDTH; x++) {
        for (int y = 0; y<POLICY_HEIGHT; y++) {
            if (y ==  floor(POLICY_HEIGHT/2) && x == floor(POLICY_WIDTH/2)) {
                printf("X "); // center; no move required
            } else {
                printf("%s ", utils.getStringFromAction(utils.getOppositeAction(randomPolicy[x][y])).c_str());
            }
        }
        printf("\n");
    }
}

void Policy::writePolicyToFile(string filename) {
    ofstream file;
    file.open (filename + ".txt");
    for (int x = 0; x<POLICY_WIDTH; x++) {
        for (int y = 0; y<POLICY_HEIGHT; y++) {
            if (y ==  floor(POLICY_HEIGHT/2) && x == floor(POLICY_WIDTH/2)) {
                file << "X "; // center
            } else {
                file << utils.getStringFromAction(utils.getOppositeAction(randomPolicy[x][y])).c_str();
                file << " ";
            }
        }
        file << "\n";
    }
    file.close();
}
