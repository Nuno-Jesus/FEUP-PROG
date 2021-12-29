// T09_G02
#include "Gate.hpp"

using namespace std;


/** \brief Default constructor for the 'Gate' class */
Gate :: Gate(){

}


/**
 * \brief Overloaded constructor for the 'Gate' class
 * \param xPos X coordinate of the gate object
 * \param yPos Y coordinate of the gate object
 */
Gate :: Gate(unsigned int xPos, unsigned int yPos){
  this->x = xPos;
  this->y = yPos;
}


/**
 * \brief Gets the X coordinate of a 'Gate' object
 * \return X coordinate
 */
unsigned int Gate :: getXPos() const{
  return x;
}


/**
 * \brief Gets the Y coordinate of a 'Gate' object
 * \return Y coordinate
 */
unsigned int Gate :: getYPos() const{
  return y;
}


/**
 * \brief Sets new positions for the 'Gate' object
 * \param xPos New X coordinate
 * \param yPos New Y coordinate
 */
void Gate :: setPos(unsigned int xPos, unsigned int yPos){
  this->x = xPos;
  this->y = yPos;
}
