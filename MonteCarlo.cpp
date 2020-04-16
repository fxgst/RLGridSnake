#include "MonteCarlo.hpp"

Policy MonteCarlo::firstVisitMCPredictionStates(Policy p) {
    printf("Initializing...\n");
    
    // generate empty state values
    double value_s[p.POLICY_WIDTH][p.POLICY_HEIGHT];    
    // generate empty list for returns for every state
    std::vector<double> returns_s[p.POLICY_WIDTH][p.POLICY_HEIGHT];
        
    printf("Done!\n");

    printf("Predicting value of states...\n");

    for (int e = 0; e<utils.EPISODES; e++) {
        Game g = Game();
        vector<Step> episode = g.generateEpisode(p);

        double g_return = 0;

        for (int t = (int) episode.size()-1-1; t >= 0; t-=1) {
            g_return = utils.GAMMA * g_return + episode[t+1].reward;
            
            int s_x_t = episode[t].x_distance;
            int s_y_t = episode[t].y_distance;
            
            bool firstVisit = true;
            for (int before_t = 0; before_t < t; before_t++) {
                if (episode[before_t].x_distance == s_x_t && episode[before_t].y_distance == s_y_t) {
                    firstVisit = false;
                    break;
                }
            }
            
            if (firstVisit) {
                int x = s_x_t + utils.BOARD_WIDTH-1;
                int y = s_y_t + utils.BOARD_HEIGHT-1;
                returns_s[x][y].push_back(g_return);
                value_s[x][y] = average(returns_s[x][y]);
            }
            
        }
    }

    printf("Done!\n");
    return p;
}

Policy MonteCarlo::exploringStartsMC(Policy p) {
    printf("Initializing...\n");

    // generate value function for every state-action pair
    double value_s_a[4][p.POLICY_WIDTH][p.POLICY_HEIGHT];    
    // generate empty list for returns for every state-action pair
    std::vector<double> returns_s_a[4][p.POLICY_WIDTH][p.POLICY_HEIGHT];

    printf("Done!\n");

    printf("Learning...\n");

    for (int e = 0; e<utils.EPISODES; e++) {
        Game g = Game();
        vector<Step> episode = g.generateEpisode(p);

        double g_return = 0;
        for (int t = (int) episode.size()-1-1; t >= 0; t-=1) {
            g_return = utils.GAMMA * g_return + episode[t+1].reward;
            
            int s_x_t = episode[t].x_distance;
            int s_y_t = episode[t].y_distance;
            Action a_t = episode[t].action;
            
            bool firstVisit = true;
            for (int before_t = 0; before_t < t; before_t++) {
                if (episode[before_t].x_distance == s_x_t && episode[before_t].y_distance == s_y_t && episode[before_t].action == a_t) {
                    firstVisit = false;
                    break;
                }
            }
            
            if (firstVisit) {
                int x_index = s_x_t + utils.BOARD_WIDTH-1;
                int y_index = s_y_t + utils.BOARD_HEIGHT-1;

                returns_s_a[a_t][x_index][y_index].push_back(g_return);
                value_s_a[a_t][x_index][y_index] = average(returns_s_a[a_t][x_index][y_index]);
                
                // greedily choose best action for state
                double argmax = LONG_MIN;
                int action = -1;
                for (int i = 0; i<4; i++) {
                    double value = value_s_a[i][x_index][y_index];
                    if (argmax < value) {
                        argmax = value;
                        action = i;
                    }
                }
                p.randomPolicy[x_index][y_index] = utils.getActionFromInt(action);
            }
            
        }
    }

    printf("Done!\n");
    return p;
}

double MonteCarlo::average(std::vector<double> v) {
    double sum = 0;
    for (int i = 0; i<v.size(); i++) {
        sum += v[i];
    }
    return sum/v.size();
}
