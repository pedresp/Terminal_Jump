#ifndef __Obstacle__
#define __Obstacle__

#include "structs.h"

class Obstacle {
  protected:
    position pos;
    int width;
    int height;

  public:
    virtual bool advance_1_step() = 0;
    virtual void draw() = 0;
    position getPos();
    int getY();
    int getX();
    int getWidth();
    int getHeight();

    virtual ~Obstacle() = 0;
};

class Box : public Obstacle {
  public:
    Box(int, int, int = 1, int = 1);

    bool advance_1_step();
    void draw();

    ~Box();
};

#endif