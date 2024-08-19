#ifndef __Jumper__
#define __Jumper__

#include "structs.h"

class Jumper {
  private:
    position pos;

    // int jump_stage;
    int jump_height, jump_starting_point;

    char repr;
    bool up, floor, jumping;

    int jump_delay, jump_delay_stage;

  public:
    Jumper(int, int = 3, int = 2);

    void restart();

    void step(char);
    void landed();
    position getPos();
    int getY();
    int getX();
    bool getUp();
    void resetFloor();

    ~Jumper();
};

#endif