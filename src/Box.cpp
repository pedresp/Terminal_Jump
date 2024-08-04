#include "Obstacle.h"
#include <ncurses.h>

Box::Box(int y, int x, int height) {
    pos.x = x;
    pos.y = y;

    height = height;
}

bool Box::advance_1_step(){
    mvaddch(pos.y, pos.x, ' ');
    pos.x--;

    attron(COLOR_PAIR(10));
    mvaddch(pos.y, pos.x, ' ');
    attroff(COLOR_PAIR(10));

    return pos.x > -1;
}

Box::~Box(){}