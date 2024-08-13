#include "Obstacle.h"

position Obstacle::getPos() { return this->pos; }

int Obstacle::getY() { return this->pos.y; }

int Obstacle::getX() { return this->pos.x; }

int Obstacle::getWidth() { return this->width; }

int Obstacle::getHeight() { return this->height; }

Obstacle::~Obstacle() {}