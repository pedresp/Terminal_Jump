#include "Parser.h"
#include <cctype>
#include <ncurses.h>

scenario_states state0(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&);
scenario_states state1(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int);
scenario_states state2(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int = 1);
scenario_states state3(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int = 1, int = 1);
scenario_states state4(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int);
scenario_states state5(std::istream&, std::vector<std::unique_ptr<Obstacle>>&, int&, int, int);

scenario_states state0(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec, int& count){
    char c;
    is.get(c);
    move(3, 0);
    printw("%c", c);

    if (!c)
        return CORRECT_SCENARIO;
    else if (c == '_')
        return state2(is, vec, count);
    else if (c == '|')
        return state3(is, vec, count); 
    else if (isdigit(c))
        return state1(is, vec, count, c - 48);
    
    return UNEXPECTED_CHAR;
}

scenario_states read_scenario(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec){
    int count = 0;

    return state0(is, vec, count);
}