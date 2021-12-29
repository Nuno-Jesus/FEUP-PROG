// T09_G02
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <chrono>

#include <cstring>

#include "Maze.hpp"
#include "Robot.hpp"
#include "Player.hpp"

using namespace std;
using namespace std::chrono;

typedef enum moves_ {
  MOVE_LEFT_UP, MOVE_LEFT, MOVE_LEFT_DOWN, 
  STAY, MOVE_UP, MOVE_DOWN, MOVE_RIGHT_UP, 
  MOVE_RIGHT, MOVE_RIGHT_DOWN, INVALID
} Move;
  
bool isLineModifier(const char c);

class Game{
  public:
    Game();    
    Game(const string fileName);

    double play();
    void displayMaze();
    
    Player getPlayer();
    
  private:
    Move readMove();
    Move movePlayer(const Move move);
    void moveAllRobots();
    void moveOneRobot(const int i, int &botX, int &botY, int &deltaX, int &deltaY);

    bool playerCollided(const Robot robot);                        
    bool playerCollided(const Post post);             
    bool playerCollided(const Gate gate);

    bool botCollided(const Robot r1, const Robot r2);
    bool botCollided(const Robot robot, const Post post);
    bool botCollided(const Robot robot, const Gate gate);
    bool botCollided(const Robot robot);            
    
    bool checkGameOver();

    void cleanMazeFrame();
    void drawMazeFrame();

    unsigned int getNumRobots();
    unsigned int getNumAliveRobots();

    void clearScreen();
    
  private:
    Maze maze;
    Player player;
    vector<Robot> robots;

    unsigned int numRobots;
    unsigned int numAliveRobots;
};

#endif