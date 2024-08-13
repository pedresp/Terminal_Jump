#ifndef __Obstacle__
#define __Obstacle__

#include "structs.h"

class Obstacle {
  protected:
    position pos;
    int width;

  public:
    virtual bool advance_1_step() = 0;
    position getPos();
    int getY();
    int getX();
    int getWidth();

    virtual ~Obstacle() = 0;
};

class Box : public Obstacle {
  private:
    int height;

  public:
    Box(int, int, int = 1, int = 1);

    bool advance_1_step();

    ~Box();
};

#endif