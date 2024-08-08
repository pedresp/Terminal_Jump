#ifndef __Jumper__
#define __Jumper__

#include "structs.h"

class Jumper {
  private:
    position pos;

    int jump_stage;
    int jump_height;

    char repr;
    bool up;

  public:
    Jumper(int, int = 3);

    void step(char);

    ~Jumper();
};

#endif