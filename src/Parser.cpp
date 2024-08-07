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

scenario_states state1(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec, int& count, int height){
    char c;
    is.get(c);
    printw("%c", c);

    if (!c)
        return NO_OBSTACLE_SPECIFIED;
    else if (isdigit(c))
        return state1(is, vec, count, 10 * height + c - 48);
    else if (c == '_')
        return state2(is, vec, count, height);
    else if (c == '|')
        return state3(is, vec, count, height);
    else if (c == 'x')
        return state4(is, vec, count, height);

    return UNEXPECTED_CHAR;
}

scenario_states state2(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec, int& count, int width){
    char c;
    is.get(c);
    printw("%c", c);

    count += width;

    if (!c)
        return CORRECT_SCENARIO;
    else if (isdigit(c))
        return state1(is, vec, count, c - 48);
    else if (c == '_')
        return state2(is, vec, count);
    else if (c == '|')
        return state3(is, vec, count);

    return UNEXPECTED_CHAR;
}

scenario_states state3(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec, int& count, int height, int width){
    char c;
    is.get(c);
    printw("%c", c);

    //add obstacle
    vec.push_back(std::make_unique<Box>(LINES - 1, count, height, width));

    count += width;    

    if (!c)
        return CORRECT_SCENARIO;
    else if (isdigit(c))
        return state1(is, vec, count, c - 48);
    else if (c == '_')
        return state2(is, vec, count);
    else if (c == '|')
        return state3(is, vec, count);

    return UNEXPECTED_CHAR;
}

scenario_states state4(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec, int& count, int height){
    char c;
    is.get(c);
    printw("%c", c);

    if (!c)
        return NO_WIDTH_SPECIFIED;
    else if (isdigit(c))
        return state5(is, vec, count, height, c - 48);
    
    return UNEXPECTED_CHAR;
}
scenario_states read_scenario(std::istream& is, std::vector<std::unique_ptr<Obstacle>>& vec){
    int count = 0;

    return state0(is, vec, count);
}