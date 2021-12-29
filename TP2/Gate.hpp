// T09_G02
#ifndef GATE_H
#define GATE_H

#include <iostream>

using namespace std;

class Gate{
  public:
    Gate();
    Gate(unsigned int xPos, unsigned int yPos);

    unsigned int getXPos() const;
    unsigned int getYPos() const;

    void setPos(unsigned int xPos, unsigned int yPos);

  private:
    unsigned int x, y;
};

#endif