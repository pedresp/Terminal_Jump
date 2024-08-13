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

    int jump_delay, jump_delay_stage;

  public:
    Jumper(int, int = 3, int = 2);

    void step(char);

    ~Jumper();
};

#endif