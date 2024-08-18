#include "Obstacle.h"

Obstacle::Obstacle(int y, int x, int height, int width) {
    this->pos.y = y;
    this->pos.x = x;

    this->height = height;
    this->width = width;

    this->r_pos = this->pos;
}

void Obstacle::restart() { this->pos = this->r_pos; }

position Obstacle::getPos() { return this->pos; }

int Obstacle::getY() { return this->pos.y; }

int Obstacle::getX() { return this->pos.x; }

int Obstacle::getWidth() { return this->width; }

int Obstacle::getHeight() { return this->height; }

Obstacle::~Obstacle() {}