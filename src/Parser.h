#ifndef __Parser__
#define __Parser__

#include <istream>
#include <memory>
#include <vector>

#include "Obstacle.h"

enum scenario_states {
    CORRECT_SCENARIO = 0,
    UNEXPECTED_CHAR = 1,
    NO_OBSTACLE_SPECIFIED = 2,
    NO_WIDTH_SPECIFIED = 3,
    NOT_VALID_HEIGHT = 4,
    NOT_VALID_WIDTH = 5
};

scenario_states read_scenario(std::istream&, std::vector<std::unique_ptr<Obstacle>>&);

#endif