// T09_G02
#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>

using namespace std;

class Robot{
  public:
    Robot();
    Robot(unsigned int xPos, unsigned int yPos, unsigned int id, bool state);
    
    unsigned int getXPos() const;
    unsigned int getYPos() const;
    unsigned int getID() const;
    bool isDestroyed() const;

    void setPos(unsigned int xPos, unsigned int yPos);
    void setID(unsigned int id);
    void setStuckState(bool state);

  private:
    unsigned int x;
    unsigned int y;
    unsigned int id;
    bool isStuck;
};

#endif