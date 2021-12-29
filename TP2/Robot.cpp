// T09_G02
#include "Robot.hpp"

using namespace std;


/** \brief Default constructor for the 'Robot' class */
Robot :: Robot(){

}


/** 
 * \brief Overloaded constructor for the 'Robot' class 
 * \param xPos X coordinate of the robot
 * \param yPos Y coordinate of the robot
 * \param id Identification number for the robot
 * \param state True if the robot is stuck, false otherwise
*/
Robot :: Robot(unsigned int xPos, unsigned int yPos, unsigned int id, bool state){
    this->x = xPos;
    this->y = yPos;
    this->id = id;
    this->isStuck = state;
}


/** \brief Returns the X coordinate of the robot */
unsigned int Robot :: getXPos() const{
    return x;
}


/** \brief Returns the Y coordinate of the robot */
unsigned int Robot :: getYPos() const{
    return y;
}


/** \brief Returns the ID of the robot */
unsigned int Robot :: getID() const{
    return id;
}


/** \brief Returns the stuck state of the robot */
bool Robot :: isDestroyed() const{
    return isStuck;
}


/** 
 * \brief Sets new coordinates for the robot
 * \param xPos New X coordinate
 * \param yPos New Y coordinate 
*/
void Robot :: setPos(unsigned int xPos, unsigned int yPos){
    this->x = xPos;
    this->y = yPos;
}


/** \brief Sets a new ID for the robot */
void Robot :: setID(unsigned int id){
    this->id = id;
}


/** \brief Sets a new stuck state for the robot */
void Robot :: setStuckState(bool state){
    this->isStuck = state;
}




