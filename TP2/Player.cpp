// T09_G02
#include "Player.hpp"

using namespace std;



/** \brief Default constructor for the 'Player' class */
Player :: Player(){

}


/** 
 * \brief Overloaded constructor for the 'Player' class 
 * \param xPos X coordinate of the player
 * \param yPos Y coordinate of the player 
*/
Player :: Player(unsigned int xPos, unsigned int yPos, bool state){
    this->x = xPos;
    this->y = yPos;
    this->wasEletrocuted = false;
    this->wasRobotKilled = false;
    this->killedAllRobots = false;
    this->foundGate = false;
    this->isDead = state;
}


/** \brief Returns the X coordinate of the player */
unsigned int Player :: getXPos() const{
    return x;
}


/** \brief Returns the Y coordinate of the player */
unsigned int Player :: getYPos() const{
    return y;
}


/** \brief Returns the eletrified state of the player */
bool Player :: wasEletrified() const{
    return wasEletrocuted;
}


/** \brief Returns the state about being killed by a robot */
bool Player :: wasKilledByRobot() const{
    return wasRobotKilled;
}

/** \brief Returns true if the player started dead */
bool Player :: startedDead() const{
    return isDead;
}


/** \brief Returns the state about finding a gate */
bool Player :: hasFoundGate() const{
    return foundGate;
}


/** \brief Returns the state about all robots being dead */
bool Player :: hasKilledAllRobots() const{
    return killedAllRobots;
}


/** 
 * \brief Sets the new X and Y coordinates for the player
 * \param xPos New X coordinate
 * \param yPos New Y coordinate
*/
void Player :: setPos(unsigned int xPos, unsigned int yPos){
    this->x = xPos;
    this->y = yPos;
}


/** \brief Sets the new state for being eletrocuted */
void Player :: setElectrocuted(bool state){
    this->wasEletrocuted = state;
}


/** \brief Sets the new state for being killed by a robot */
void Player :: setRobotKilled(bool state){
    this->wasRobotKilled = state;
}


/** \brief Sets the new state for finding a gate */
void Player :: setFoundGate(bool state){
    this->foundGate = state;
}


/** \brief Sets the new state for all robots being dead */
void Player :: setKilledAllRobots(bool state){
    this->killedAllRobots = state;
}


