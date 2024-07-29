#ifndef __Obstacle__
#define __Obstacle__

#include "structs.h"

class Obstacle {
  protected:
    position pos;

  public:
    bool advance_1_step();

    virtual ~Obstacle() = 0;
};

class Box : Obstacle {
  private:
    int height;

  public:
    Box(int, int, int = 1);
    ~Box();
};

#endif