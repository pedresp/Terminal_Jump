#include "Obstacle.h"
#include <ncurses.h>

Box::Box(int y, int x, int height, int width) : Obstacle(y, x, height, width) {}

void Box::draw() {
    // draw complete obstacle
    for (int i = 0; i < width; i++) {
        attron(COLOR_PAIR(10));
        mvvline(pos.y - height + 1, pos.x + i, ' ', height);
        attroff(COLOR_PAIR(10));
    }
}

bool Box::advance_1_step() {
    pos.x--;

    // remove previous line
    if (pos.x + width < COLS)
        mvvline(pos.y - height + 1, pos.x + width, ' ', height);

    // add new column
    if (pos.x < COLS && pos.x >= 0) {
        attron(COLOR_PAIR(10));
        mvvline(pos.y - height + 1, pos.x, ' ', height);
        attroff(COLOR_PAIR(10));
    }

    return pos.x + width > 0;
}

Box::~Box() {}