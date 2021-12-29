// T09_G02
#ifndef HIGHSCORES_H
#define HIGHSCORES_H


#include <iostream>
#include <vector>

#include "Winners.hpp"

using namespace std;

class Highscores{
  public:
    void bubbleSort();
    void swap(Winners &w1, Winners &w2);
    void addWinner(const Winners w);

    void readWinners(fstream &f);
    void writeWinners(fstream &f);
    bool buildFileWinnersName(string &fileName, int &mazeN);
    void displayWinners(const string filename);
    
  private:
    bool fileIsEmpty(fstream &f);
  
  private: 
    vector<Winners> winners;
};

#endif