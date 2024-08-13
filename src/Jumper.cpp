#include "Jumper.h"
#include <ncurses.h>

Jumper::Jumper(int x, int jump_height, int jump_delay) {
    this->pos.x = x;
    this->pos.y = LINES - 1;

    this->jump_stage = 0;
    this->jump_height = jump_height;

    this->repr = 'x';
    this->up = false;

    this->jump_delay = jump_delay;
    this->jump_delay_stage = 0;
}

void Jumper::step(char c) {
    if (jump_stage) {
        if (jump_stage == jump_height)
            up = false;

        jump_delay_stage = (jump_delay_stage + 1) % jump_delay;
        if (!jump_delay_stage || (jump_stage == 1 && !up)) {
            jump_stage = (up) ? jump_stage + 1 : jump_stage - 1;
            repr = (jump_stage % 2) ? '+' : 'x';

            int prev_y = pos.y;
            pos.y = (up) ? pos.y - 1 : pos.y + 1;

            mvaddch(pos.y, pos.x, repr);
            mvaddch(prev_y, pos.x, ' ');
        }
    } else if (c != '\0') {
        up = true;
        jump_stage = 1;

        jump_delay_stage = 1;

        --pos.y;
        mvaddch(pos.y, pos.x, '+');
        mvaddch(pos.y + 1, pos.x, ' ');
    }
}

position Jumper::getPos() { return this->pos; }

int Jumper::getY() { return this->pos.y; }

int Jumper::getX() { return this->pos.x; }

Jumper::~Jumper() {}