// T09_G02
#include "Maze.hpp"

using namespace std;



/** \brief Default constructor for the 'Maze' class */
Maze :: Maze(){

}


/** 
 * \brief Overloaded constructor for the 'Maze' class. 
 * \param rows Number of rows of the maze
 * \param cols Number of columns of the maze
*/
Maze :: Maze(unsigned int rows, unsigned int cols){
    this->rows = rows;
    this->cols = cols;
    this->numGates = 0;
    this->numPosts = 0;
}


/** 
 * \brief Adds a 'Post' object to the 'Post' class vector 
 * \param post 'Post' object to be added
*/
void Maze :: addPost(const Post post){
    posts.push_back(post);
    numPosts++;
}


/** 
 * \brief Adds a 'Gate' object to the 'Gate' class vector 
 * \param post 'Gate' object to be added
*/
void Maze :: addGate(const Gate gate){
    gates.push_back(gate);
    numGates++;
}


/** \brief Adds a new symbol to the maze map */
void Maze :: addElement(const char elem){
    mazeMap.push_back(elem);
}


/** 
 * \brief Sets the symbol in a position 'pos' in the maze map
 * \param pos Index of the position to store the symbol at
 * \param c Symbol to store
 */ 
void Maze :: setElement(int pos, char c){
    mazeMap.at(pos) = c;
}


/** \brief Returns the rows of the maze */
unsigned int Maze :: getRows() const{
    return rows;
}


/** \brief Returns the columns of the maze */
unsigned int Maze :: getCols() const{
    return cols;
}


/** \brief Returns the number of posts of the maze */
unsigned int Maze :: getNumPosts() const{
    return numPosts;
}


/** \brief Returns the number of gates of the maze */
unsigned int Maze :: getNumGates() const{
    return numGates;
}


/** 
 * \brief Returns a 'Post' object out of the 'Post' vector 
 * \param pos Position where the object is stored
*/
Post Maze :: getPost(unsigned int pos) const{
    return posts.at(pos);
}


/** 
 * \brief Returns a 'Gate' object out of the 'Gate' vector 
 * \param pos Position where the object is stored
 */
Gate Maze :: getGate(unsigned int pos) const{
    return gates.at(pos);
}


/** 
 * \brief Returns a symbol out of the maze map 
 * \param pos Position where the object is stored
 */
char Maze :: getElement(unsigned int pos) const{
    return mazeMap.at(pos);
}