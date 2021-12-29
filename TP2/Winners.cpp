// T09_G02
#include "Winners.hpp"

using namespace std;

/** \brief Default constructor for 'Highscores' class */
Winners :: Winners(){

}

/**
 * \brief Overloaded constructor for the 'Highscores' class
 * \param fName Winner's first name
 * \param sName Winner's second name
 * \param time Time to win
*/
Winners :: Winners(string fName, string sName, int time){
  this->fName = fName;
  this->sName = sName;
  this->time = time;
}

/** \brief Returns the winner's first name */
string Winners :: getFName(){
  return this->fName;
}

/** \brief Returns the winner's second name */
string Winners :: getSName(){
  return this->sName;
}

/** \brief Returns the winner's time to win */
int Winners :: getTime(){
  return this->time;
}
