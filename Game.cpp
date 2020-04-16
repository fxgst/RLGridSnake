#include "Game.hpp"

//                y (height)
//          (0,0)------------>
//            |
//            |
//      x     |
//   (width)  |
//            \/
//

Game::Game() {
    x_apple = utils.getRandomFromTo(0, utils.BOARD_WIDTH-1);
    y_apple = utils.getRandomFromTo(0, utils.BOARD_HEIGHT-1);
    x_snake = utils.getRandomFromTo(0, utils.BOARD_WIDTH-1);
    y_snake = utils.getRandomFromTo(0, utils.BOARD_HEIGHT-1);
    
    while (x_snake == x_apple && y_snake == y_apple) {
        x_snake = utils.getRandomFromTo(0, utils.BOARD_WIDTH-1);
        y_snake = utils.getRandomFromTo(0, utils.BOARD_HEIGHT-1);
    }
    
    x_distance = x_apple - x_snake;
    y_distance = y_apple - y_snake;
}

// look up action in policy
Action Game::getActionFromPolicy(Policy p) {
    int x_policy = x_distance + utils.BOARD_WIDTH-1;
    int y_policy = y_distance + utils.BOARD_HEIGHT-1;
    
    Action action = p.randomPolicy[x_policy][y_policy];
    return action;
}

std::vector<Step> Game::generateEpisode(Policy p) {
    std::vector<Step> episode;
        
    Step first;
    // set reward
    first.reward = (int) NULL;
    // set state
    first.x_distance = x_distance;
    first.y_distance = y_distance;

    // set first action
    // first.action = getActionFromPolicy(p);
    
    // random start action, not from policy; "exploring starts"
    first.action = utils.getActionFromInt(utils.getRandomFromTo(0, 3));

    episode.push_back(first);
    performAction(first.action);
        
    int reward;
    // as long as not outside, eaten or stuck
    int count = 1;
    while (true) {
        reward = calculateReward(count);
        
        Step nextStep;
        nextStep.reward = reward;
        nextStep.x_distance = x_distance;
        nextStep.y_distance = y_distance;
        nextStep.action = getActionFromPolicy(p);
        
        episode.push_back(nextStep);
        
        if (reward == utils.OUTSIDE_REWARD) {
            break;
        } else if (reward == utils.EATEN_REWARD) {
            break;
        } else if (reward == utils.INF_LOOP_REWARD) {
            break;
        } else if (episode.size() > 1 && episode.rbegin()[0].action == utils.getOppositeAction(episode.rbegin()[1].action)) {
            episode.rbegin()[0].reward = utils.INF_LOOP_REWARD;
            break;
        }
        
        performAction(nextStep.action);
        
        count += 1;
    }
    return episode;
}

double Game::calculateReward(int count) {
    if (count > utils.BOARD_HEIGHT*utils.BOARD_WIDTH) {
        return utils.INF_LOOP_REWARD;
    }
    if (x_snake == x_apple && y_snake == y_apple) {
        return utils.EATEN_REWARD;
    } else if (x_snake < 0 || y_snake < 0) {
        return utils.OUTSIDE_REWARD;
    } else if (x_snake >= utils.BOARD_WIDTH || y_snake >= utils.BOARD_HEIGHT) {
        return utils.OUTSIDE_REWARD;
    }
    return utils.STEP_REWARD;
}

void Game::performAction(Action action) {
    switch (action) {
        case Up:
            x_snake -= 1;
            break;
        case Down:
            x_snake += 1;
            break;
        case Left:
            y_snake -= 1;
            break;
        case Right:
            y_snake += 1;
            break;
        default:
            break;
    }
    x_distance = x_apple - x_snake;
    y_distance = y_apple - y_snake;
}

void Game::printEpisode(std::vector<Step> episode) {
    for (Step step : episode) {
        printf("%s %d %d %d\n", utils.getStringFromAction(step.action).c_str(), step.reward, step.x_distance, step.y_distance);
    }
}

void Game::printBoard() {
    for (int x = 0; x<utils.BOARD_WIDTH; x++) {
        for (int y = 0; y<utils.BOARD_HEIGHT; y++) {
            if (x == x_snake && y == y_snake) {
                printf("S ");
            } else if (x == x_apple && y == y_apple) {
                printf("A ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
