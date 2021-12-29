// T09_G02
#include "Post.hpp"

using namespace std;



/** \brief Default constructor for 'Post' class */
Post :: Post(){

}


/** 
 * \brief Overloaded constructor for the 'Post' class 
 * \param xPos X coordinate of the post
 * \param yPos Y coordinate of the post
 * \param state True if the post is eletrified, false otherwise
*/
Post :: Post(unsigned int xPos, unsigned int yPos, bool state){
    this->x = xPos;
    this->y = yPos;
    this->isEletrified = state;
}


/** \brief Returns the X coordinate of the post */
unsigned int Post :: getXPos() const{
    return x;
}


/** \brief Returns the Y coordinate of the post */
unsigned int Post :: getYPos() const{
    return y;
}


/** \brief Returns the state of the post (eletrified or non-eletrified) */
bool Post :: isEletric() const{
    return isEletrified;
}
