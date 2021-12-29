// T09_G02
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player{
  public:
    Player();
    Player(unsigned int xPos, unsigned int yPos, bool state);
        
    unsigned int getXPos() const;
    unsigned int getYPos() const;
    
    bool wasEletrified() const;
    bool wasKilledByRobot() const;
    bool startedDead() const;
    
    bool hasFoundGate() const;
    bool hasKilledAllRobots() const;

    void setPos(unsigned int xPos, unsigned int yPos);
    void setElectrocuted(bool state);
    void setRobotKilled(bool state);
    
    void setFoundGate(bool state);
    void setKilledAllRobots(bool state);

  private:
    unsigned int x;
    unsigned int y;    
    
    bool wasEletrocuted;
    bool wasRobotKilled;
    
    bool killedAllRobots;
    bool foundGate;

    bool isDead;
};

#endif