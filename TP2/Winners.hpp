// T09_G02
#ifndef WINNERS_H
#define WINNERS_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include <cstring>

using namespace std;


class Winners{
  public:
    Winners();
    Winners(string fName, string sName, int time);

    string getFName();
    string getSName();
    int getTime();

  private:
    string fName, sName;
    int time;
};


#endif