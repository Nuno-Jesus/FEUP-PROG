// T09_G02
#ifndef POST_H
#define POST_H

#include <iostream>

using namespace std;

class Post{
  public:
    Post();
    Post(unsigned int xPos, unsigned int yPos, bool state);
    
    unsigned int getXPos() const;
    unsigned int getYPos() const;
    bool isEletric() const;
    
  private:
    unsigned int x;
    unsigned int y;
    bool isEletrified;
};

#endif