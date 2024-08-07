#include "Parser.h"
#include <cctype>
#include <ncurses.h>

scenario_states state0(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&);
scenario_states state1(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int);
scenario_states state2(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int = 1);
scenario_states state3(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int = 1, int = 1);
scenario_states state4(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int);
scenario_states state5(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int, int);



scenario_states read_scenario(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec){
    int count = 0;

    return state0(is, vec, count);
}