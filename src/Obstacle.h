#ifndef __Obstacle__
#define __Obstacle__

#include "structs.h"

class Obstacle {
  protected:
    position pos;

  public:
    virtual bool advance_1_step() = 0;

    virtual ~Obstacle() = 0;
};

class Box : public Obstacle {
  private:
    int height;

  public:
    Box(int, int, int = 1);
    bool advance_1_step();
    ~Box();
};

#endif