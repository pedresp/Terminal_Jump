#include "Obstacle.h"
#include <ncurses.h>

Box::Box(int y, int x, int height) {
    pos.x = x;
    pos.y = y;

    height = height;
}