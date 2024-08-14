#include "Jumper.h"
#include <ncurses.h>

Jumper::Jumper(int x, int jump_height, int jump_delay) {
    this->pos.x = x;
    this->pos.y = LINES - 1;

    // this->jump_stage = 0;
    this->jump_height = jump_height;
    this->jump_starting_point = pos.y;

    this->repr = 'x';
    this->up = false;
    this->floor = false;
    this->jumping = false;

    this->jump_delay = jump_delay;
    this->jump_delay_stage = 0;
}

void Jumper::step(char c) {
    mvprintw(15, 0, "JUMPING: %d UP: %d FLOOR: %d", jumping, up, floor);
    if (jumping) {
        if (pos.y == jump_starting_point - jump_height)
            up = false;

        jump_delay_stage = (jump_delay_stage + 1) % jump_delay;
        if (!jump_delay_stage) { //|| (jump_stage == 1 && !up)) {
            // jump_stage = (up) ? jump_stage + 1 : jump_stage - 1;
            repr = ((LINES - 1 - pos.y) % 2) ? '+' : 'x';

            int prev_y = pos.y;
            pos.y = (up) ? pos.y - 1 : pos.y + 1;

            mvaddch(pos.y, pos.x, repr);
            mvaddch(prev_y, pos.x, ' ');

            jumping = (pos.y == LINES - 1) ? false : jumping;
        }
    } else if (LINES - 1 - pos.y && !floor) {
        ++pos.y;

        mvaddch(pos.y, pos.x, repr);
        mvaddch(pos.y - 1, pos.x, ' ');
    } else if (c != '\0') {
        up = true;
        jumping = true;
        jump_delay_stage = -1;
        jump_starting_point = pos.y;

        --pos.y;
        mvaddch(pos.y, pos.x, repr);
        mvaddch(pos.y + 1, pos.x, ' ');
    } else
        mvaddch(pos.y, pos.x, repr);
}

void Jumper::landed() {
    this->up = false;
    this->jumping = false;
    this->floor = true;
    this->jump_delay_stage = -1;
}

position Jumper::getPos() { return this->pos; }

int Jumper::getY() { return this->pos.y; }

int Jumper::getX() { return this->pos.x; }

bool Jumper::getUp() { return this->up; }

void Jumper::resetFloor() { this->floor = false; }

Jumper::~Jumper() {}