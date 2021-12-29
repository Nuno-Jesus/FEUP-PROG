// T09_G02
#include "Game.hpp"

//#define DEBUG

using namespace std;


Game :: Game(){

}


/** 
 * \brief Overloaded constructor for 'Game' class. This one is responsible for opening the file  
 * where the maze is at and parse it to initialize the 'Game' class atributes.
 * \param fileName Name of the file where the maze is at
*/
Game :: Game(const string fileName){
  unsigned int rows, cols;
  
  char c;
  int i = 0;
  fstream mazeFile;

  int robotID = 1;
  Robot auxRobot = Robot();
  Post auxPost = Post();
  Gate auxGate = Gate();

  mazeFile.open(fileName);

  /* If the file failed to be open, aborts */
  if(!mazeFile.is_open()){
    cerr << "\n\t----- FATAL ERROR: COULD NOT OPEN " << fileName << "-----\n\n";
    exit(EXIT_FAILURE);
  }

  /* Reads the maze dimensions from the first line of the file */
  mazeFile >> rows >> c >> cols;

  /* Dedug code */
  #ifdef DEBUG
    cout << "Number of rows: " << rows << endl;
    cout << "Number of cols: " << cols << endl;
    cout << endl;
  #endif

  /* If the input in file for dimensions is not a digit or negative, aborts */
  if(rows <= 0 || cols <= 0){
    cerr << "\n\t----- MAZE DIMENSIONS ARE IRREGULAR (" << rows << ", " << cols << "). ABORTING PROGRAM -----\n\n";
    exit(EXIT_FAILURE);
  }

  /* Calls maze constructor */
  this->maze = Maze(rows, cols);
  this->numRobots = 0;
  this->numAliveRobots = 0;

  /* Reads file */
  while(mazeFile.get(c)){
    if(isLineModifier(c))
      continue;

    else{
      maze.addElement(c);
      
      switch(c){
        /* Builds alive robot */
        case 'R':
          auxRobot = Robot(i % cols, i / cols, robotID++, false);
          robots.push_back(auxRobot);

          numRobots++;
          numAliveRobots++;

          break;

        /* Builds dead robot */
        case 'r':
          auxRobot = Robot(i % cols, i / cols, robotID++, true);
          robots.push_back(auxRobot);

          numRobots++;

          break;

        /* Builds alive player */
        case 'H':
          player = Player(i % cols, i / cols, false);
          
          break;

        /* Builds dead player */
        case 'h':
          player = Player(i % cols, i / cols, true);
          
          break;

        /* Builds eletrified post/fence */
        case '*':
          auxPost = Post(i % cols, i / cols, true);
          maze.addPost(auxPost);

          break;

        /* Builds non-eletrified post/fence */
        case '+':
          auxPost = Post(i % cols, i / cols, false);
          maze.addPost(auxPost);

          break;

        /* Builds gate */
        case 'O':
          auxGate = Gate(i % cols, i / cols);
          maze.addGate(auxGate);

          break;

        /* Builds empty space */
        case ' ':
          break;

        /* Displays warning message in case of irregular characters */
        default:
          cout << "\n\n----- ABNORMAL CHARACTER FOUND IN " << i << ": " << c << ". PROCEDING TO READ -----\n\n";
      }
    }

    i++;
  }

  /* Debug code */
  #ifdef DEBUG
    cout << "Number of robots: " << numRobots << endl;
    cout << "Number of alive robots: " << numAliveRobots << endl;
    cout << endl; 
  #endif

  mazeFile.close();
}


/** 
 * \brief The game main loop. This method is responsible to call nearly all other methods
 * to implement the game logic and ensure the rules are enforced.
 * \return Game time
*/
double Game :: play(){
  bool gameIsOver = false, cancelClearScreen = false;
  Move move;

  high_resolution_clock::time_point start, end; 
  duration<double> elapsedTime; 

  #ifdef DEBUG
    cancelClearScreen = true;
  #endif

  //Starts time counting
  start = high_resolution_clock :: now();

  gameIsOver = checkGameOver();
  
  while(!gameIsOver){
    displayMaze();

    /* 
    While user input is not valid or the player tries to move 
    towards a non-eletrified post or robot-pile, asks for a new input 
    */
    do{
      /* Reads user input */
      if((move = readMove()) == INVALID){
        cout << "\n\t----- INVALID MOVE: NOT A VALID LETTER -----\n\n";
        continue;
      }
      
      /* Converts the user input to move the player */
      move = movePlayer(move);
    }while(move == INVALID);

    if(!gameIsOver && !cancelClearScreen)
      clearScreen();

    moveAllRobots();
    gameIsOver = checkGameOver();

    cleanMazeFrame();
    drawMazeFrame();
  }

  /* Ends time counting */
  end = high_resolution_clock :: now();
  elapsedTime = duration_cast<std::chrono::microseconds>(end - start);

  displayMaze();

  #ifdef DEBUG
    cout << "Alive robots: " << numAliveRobots << endl;
    cout << "Destroyed Robots: " << numRobots - numAliveRobots << endl;
    cout << "Player final pos (x, y): " << player.getXPos() << " " << player.getYPos() << endl;
  #endif

  return elapsedTime.count();
}


/** \brief Displays the maze current frame. */
void Game :: displayMaze(){
  for(unsigned int i = 0; i < maze.getCols() * maze.getRows(); i++){
    cout << maze.getElement(i);

    if((i + 1) % maze.getCols() == 0)
      cout << endl;
  }

  cout << endl;
}


/********************************* PRIVATE METHODS *********************************/


/**
 * \brief Parses the user input to convert it to a valid in-game movement.
 * \return Returns an enum type regarding the type of movement
*/
Move Game :: readMove(){
  char move;
  
  cout << "Choose your movement: "; 
  cin >> move;

  if(cin.fail() && cin.eof()){
    cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
    exit(EXIT_FAILURE);
  }

  cin.ignore(10000, '\n');
  move = toupper(move);

  switch(move){
    case 'Q':
      return MOVE_LEFT_UP;

    case 'A':
      return MOVE_LEFT;

    case 'Z':
      return MOVE_LEFT_DOWN;

    case 'S':
      return STAY;

    case 'W':
      return MOVE_UP;

    case 'X':
      return MOVE_DOWN;

    case 'E':
      return MOVE_RIGHT_UP;

    case 'D':
      return MOVE_RIGHT;

    case 'C':
      return MOVE_RIGHT_DOWN;

    default:
      return INVALID; 
  }
}


/**
 * \brief Converts the enum type coming from the readMove() method into new player coordinates.
 * \param move Enum type regarding the type of movement executed
 * \return Returns INVALID if the player tries to move towards a non-eletrified post or a robot-pile, STAY otherwise
*/
Move Game :: movePlayer(const Move move){
  unsigned int deltaX = 0, deltaY = 0;
  unsigned int newX = player.getXPos(), newY = player.getYPos();
  
  switch(move){
    /* Upper left diagonal */
    case MOVE_LEFT_UP:
      deltaX--;
      deltaY--;
      break;

    /* Leftwards */
    case MOVE_LEFT:
      deltaX--;
      break;

    /* Lower left diagonal */
    case MOVE_LEFT_DOWN:
      deltaX--;
      deltaY++;
      break;

    /* Stay in position */
    case STAY:
      deltaX = deltaY = 0;
      break;

    /* Upwards */
    case MOVE_UP:
      deltaY--;
      break;

    /* Downwards */
    case MOVE_DOWN:
      deltaY++;
      break;

    /* Upper right diagonal */
    case MOVE_RIGHT_UP:
      deltaX++;
      deltaY--;
      break;

    /* Rightwards */
    case MOVE_RIGHT:
      deltaX++;
      break;

    /* Lower right diagonal */
    case MOVE_RIGHT_DOWN:
      deltaX++;
      deltaY++;
      break;

    default:
      break;
  }

  #ifdef DEBUG
    cout << endl;
    cout << "Player current pos (x, y): " << player.getXPos() << " " << player.getYPos() << endl;
  #endif

  newX = newX + deltaX;
  newY = newY + deltaY;

  /* Check for 0 <= newX < cols and 0 <= newY < rows */
  if(newX > maze.getCols() - 1 || newX < 0 || newY > maze.getRows() - 1 || newY < 0){
    cout << "\n\t----- INVALID MOVEMENT: OUT OF BOUNDS -----\n\n";

    #ifdef DEBUG
      cout << "You were trying to move to " << newX << " " << newY << " " << endl;
    #endif

    return INVALID;
  }

  /* Sets new player's position acording to user input */
  player.setPos(newX, newY);
  
  /* If the player's new position is the same as a robot pile, he goes back */
  for(unsigned int i = 0; i < getNumRobots(); i++){  
    if(playerCollided(robots.at(i))){ 
      player.setPos(newX - deltaX, newY - deltaY); 

      if(robots.at(i).isDestroyed()){
        cout << "\n\t----- INVALID MOVEMENT: ROBOT PILE AHEAD -----\n\n";
        
        #ifdef DEBUG
          cout << "Robot pile coords (x, y): ";
          cout << robots.at(i).getXPos() << " " << robots.at(i).getYPos() << endl;
          cout << endl;
        #endif

        return INVALID;
      }   

      /* If the robot ahead is not stuck, the player touches it and dies */
      else
        player.setRobotKilled(true);
      
    }
  }

  /* The same goes if the player is trying to step on a non-eletrified post */
  for(unsigned int i = 0; i < maze.getNumPosts(); i++){
    if(playerCollided(maze.getPost(i))){
      player.setPos(newX - deltaX, newY - deltaY);

      if(!maze.getPost(i).isEletric()){
        cout << "\n\t----- INVALID MOVEMENT: NON-ELETRIFIED POST AHEAD -----\n\n";
        return INVALID;
      }
      
      /* If the post/fence is eletrified, the player touches it and dies */
      else
        player.setElectrocuted(true);
    } 
  }

  /* Again, but to check if the player managed to exit successfully out of the maze */
  for(unsigned int i = 0; i < maze.getNumGates(); i++){
    if(playerCollided(maze.getGate(i))){
      player.setFoundGate(true);
    } 
  }

  return STAY;
}


/**
 * \brief Moves all robots towards the player. Calls the method 'moveOneRobot' to enforce a displacement.
 * Also checks collisions and avoids overlapping of robots and other entities.
*/
void Game :: moveAllRobots(){
  int deltaX = 0, deltaY = 0;
  int botX = 0, botY = 0;
  Post auxPost = Post();
  Gate auxGate = Gate();

  bool collisionWasDetected = false;

  for(unsigned int i = 0; i < getNumRobots(); i++){
    if(robots.at(i).isDestroyed())
      continue;
    
    moveOneRobot(i, botX, botY, deltaX, deltaY);

    /* (Robot <-> robot) collision check */
    for(unsigned int k = 0; k < getNumRobots(); k++){
      if(k != i){
        if(botCollided(robots.at(i), robots.at(k))){
          #ifdef DEBUG
            cout << "Robot " << i + 1 << " collided " << "at: " << robots.at(i).getXPos() << " " << robots.at(i).getYPos() << endl;
            cout << endl;
          #endif

          /* If the robot collided with a robot pile, it only decrements once */
          numAliveRobots--;
          robots.at(i).setStuckState(true);

          if(!robots.at(k).isDestroyed()){
            numAliveRobots--;
            robots.at(k).setStuckState(true);
          }

          collisionWasDetected = true;
          break;
        }
      }
    }

    if(collisionWasDetected){
      collisionWasDetected = false;
      continue;
    }

    /* (Robot <-> Post) collision check */
    for(unsigned int k = 0; k < maze.getNumPosts(); k++){
      auxPost = maze.getPost(k);

      if(botCollided(robots.at(i), auxPost)){
        robots.at(i).setStuckState(true);
        numAliveRobots--;

        /* Debug code */
        #ifdef DEBUG
          cout << "Robot " << i + 1 << " eletrified " <<  "at: " << robots.at(i).getXPos() << " " << robots.at(i).getYPos() << endl;
          cout << endl;
        #endif
          
        /* If the post is eletrified, the robot doens't need to take its place */
        if(auxPost.isEletric())
          robots.at(i).setPos(botX - deltaX, botY - deltaY);

        collisionWasDetected = true;
        break; 
      }
    }

    if(collisionWasDetected){
      collisionWasDetected = false;
      continue;
    }

    /* (Robot <-> Gate) collision check */
    for(unsigned int k = 0; k < maze.getNumGates(); k++){
      auxGate = maze.getGate(k);

      if(botCollided(robots.at(i), auxGate)){
        /* Debug code */
        #ifdef DEBUG
          cout << "Robot " << i + 1 << " hitted a gate " <<  "at: " << robots.at(i).getXPos() << " " << robots.at(i).getYPos() << endl;
          cout << endl;
        #endif
          
        robots.at(i).setPos(botX - deltaX, botY - deltaY); 
        collisionWasDetected = true;
        break;
      }
    }

    if(collisionWasDetected){
      collisionWasDetected = false;
      continue;
    }

    /* (Robot <-> Player) collision check */
    if(botCollided(robots.at(i))){
      if(!player.hasFoundGate())
        player.setRobotKilled(true);

      /* Debug code */
      #ifdef DEBUG
        cout << "Robot " << i + 1 << " killed player " << "at: " << robots.at(i).getXPos() << " " << robots.at(i).getYPos() << endl;
        cout << endl;
      #endif

      /* If the robot hits the player, the bot doesn't need to take his place */
      robots.at(i).setPos(botX - deltaX, botY - deltaY);
    }
    
    collisionWasDetected = false;
    deltaX = deltaY = 0;
  }

  /* Debug code */
  #ifdef DEBUG
    cout << "Alive Robots: " << numAliveRobots << endl;
    cout << endl;
  #endif

  if(numAliveRobots == 0){
    player.setKilledAllRobots(true);
    cout << "\n\t----- ALL ROBOTS ARE DOWN! ESCAPE THROUGH A GATE TO FINISH! -----\n\n";
  }
}

/**
 * \brief Moves one robot by enforcing a displacement of 1 unit in X axis, Y axis or both.
 * \param i Index of the 'Robot' class vector to move
 * \param botX X coordinate of the robot to be recorded
 * \param botY Y coordinate of the robot to be recorded
 * \param deltaX X axis displacement to be recorded
 * \param delta Y axis displacement to be recorded
*/

void Game :: moveOneRobot(const int i, int &botX, int &botY, int &deltaX, int &deltaY){
  botX = robots.at(i).getXPos();
  botY = robots.at(i).getYPos();
    
  /* Robots moves one step closer to the player */
  if(botX < player.getXPos())                    
    deltaX = 1;

  /* Robots moves one step closer to the player */
  else if(botX > player.getXPos())               
    deltaX = -1;

  /* Robots moves one step closer to the player */
  if(botY < player.getYPos())                    
    deltaY = 1;

  /* Robots moves one step closer to the player */
  else if(botY > player.getYPos())               
    deltaY = -1;

  botX = botX + deltaX;
  botY = botY + deltaY;

  robots.at(i).setPos(botX, botY);
}


/************************** PLAYER COLLISIONS **************************/


/**
 * \brief Checks for collision between the player and a robot (equal coordinates).
 * \param robot Robot to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: playerCollided(const Robot robot){
  if(player.getXPos() == robot.getXPos() && player.getYPos() == robot.getYPos())
    return true;

  return false;
}


/**
 * \brief Checks for collision between the player and a post (equal coordinates).
 * \param post Post to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: playerCollided(const Post post){
  if(player.getXPos() == post.getXPos() && player.getYPos() == post.getYPos())
    return true;
  
  return false;
}


/**
 * \brief Checks for collision between the player and a gate (equal coordinates).
 * \param gate Gate to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: playerCollided(const Gate gate){
  if(player.getXPos() == gate.getXPos() && player.getYPos() == gate.getYPos()){
    player.setFoundGate(true);
    return true;
  }

  return false;
}


/************************** ROBOTS COLLISIONS **************************/


/**
 * \brief Checks for collision between a robot and another robot (equal coordinates).
 * \param r1 First robot to be parsed
 * \param r2 Second robot to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: botCollided(const Robot r1, const Robot r2){
  if(r1.getXPos() == r2.getXPos() && r1.getYPos() == r2.getYPos())
    return true;

  return false;
}


/**
 * \brief Checks for collision between a robot and a post (equal coordinates).
 * \param robot Robot to be parsed
 * \param post Post to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: botCollided(const Robot robot, const Post post){
  if(robot.getXPos() == post.getXPos() && robot.getYPos() == post.getYPos())
    return true;

  return false;
}

/**
 * \brief Checks for collision between a robot and a gate (equal coordinates).
 * \param robot Robot to be parsed
 * \param gate Gate to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: botCollided(const Robot robot, const Gate gate){
  if(robot.getXPos() == gate.getXPos() && robot.getYPos() == gate.getYPos())
    return true;

  return false;
}


/**
 * \brief Checks for collision between a robot and the player (equal coordinates).
 * \param robot Robot to be parsed
 * \return Returns true if the collision has occured, false otherwise
*/
bool Game :: botCollided(const Robot robot){
  if(robot.getXPos() == player.getXPos() && robot.getYPos() == player.getYPos()){
    return true;
  }

  return false;
}

/************************* GAME OVER CHECKING **************************/

/**
 * \brief Checks game over occasions: 
 * -> Player escaped.
 * -> All robots are stuck and player escaped.
 * -> Player was eletrocuted.
 * -> Player was killed by a robot.
 * -> Player started dead when the maze was read.
 * \return Returns true if the game is over, false otherwise
*/
bool Game :: checkGameOver(){
  if(player.hasFoundGate() && player.hasKilledAllRobots()){
    cout << "\n\t----- CONGRATULATIONS! YOU MANAGED TO KILL ALL ROBOTS! -----\n\n";
    return true;
  }

  if(player.hasFoundGate()){
    cout << "\n\t----- CONGRATULATIONS! YOU MANAGED TO ESCAPE! -----\n\n";
    return true;
  }
  
  else if(player.startedDead()){
    cout << "\n\t----- UNLUCKY: YOU DIED BEFORE YOU TRIED! -----\n\n";
    return true;
  }

  if(player.wasEletrified()){
    cout << "\n\t----- GAME OVER: YOU HAVE BEEN ELETROCUTED! -----\n\n";
    return true;
  }

  else if(player.wasKilledByRobot()){
    cout << "\n\t----- GAME OVER: A ROBOT KILLED YOU! -----\n\n";
    return true;
  }

  return false;
}


/*************************** MAZE MAP UPDATE ***************************/


/** \brief Cleans the maze map by setting all position to whitespaces. */
void Game :: cleanMazeFrame(){
  for(unsigned int i = 0; i < maze.getRows() * maze.getCols(); i++){
    maze.setElement(i, ' ');
  }
}


/** \brief Draws the new maze frame after the player and the robots moved.*/
void Game :: drawMazeFrame(){
  Post auxPost = Post();
  Gate auxGate = Gate();

  int x, y, pos;
  
  /* Draw all the posts */
  for(unsigned int i = 0; i < maze.getNumPosts(); i++){
    auxPost = maze.getPost(i);
    x = auxPost.getXPos();
    y = auxPost.getYPos();

    pos = y * maze.getCols() + x;
    
    if(auxPost.isEletric())
      maze.setElement(pos, '*');
    
    else
      maze.setElement(pos, '+');
  }

  /* Draw all the gates */
  for(unsigned int i = 0; i < maze.getNumGates(); i++){
    auxGate = maze.getGate(i);
    x = auxGate.getXPos();
    y = auxGate.getYPos();

    pos = y * maze.getCols() + x;
    
    maze.setElement(pos, 'O');
  }

  /* Draw all the robots */
  for(unsigned int i = 0; i < getNumRobots(); i++){
    x = robots.at(i).getXPos();
    y = robots.at(i).getYPos();

    pos = y * maze.getCols() + x;
    
    if(robots.at(i).isDestroyed())
      maze.setElement(pos, 'r');
    
    else
      maze.setElement(pos, 'R');
  }

  x = player.getXPos();
  y = player.getYPos();

  pos = y * maze.getCols() + x;

  if(player.wasEletrified() || player.wasKilledByRobot())
    maze.setElement(pos, 'h');

  else
    maze.setElement(pos, 'H');
}


/* ************************** ROBOTS NUMBERS *************************** */


unsigned int Game :: getNumRobots(){
  return numRobots;
}

unsigned int Game :: getNumAliveRobots(){
  return numAliveRobots;
}


/* **************************** MISCELLANEOUS **************************** */


/** \brief Helper function to read the maze in the 'Game' class constructor.
 * Checks if the character read is one of the 3 below.
*/
bool isLineModifier(const char c){
  char modifiers[] = {'\n', '\r', '\t'};

  for(int i = 0; i < 3; i++){
    if(c == modifiers[i])
      return true;
  }

  return false;
}

/** \brief Clears the console */
void Game :: clearScreen(){
  cout << "\033[2J\033[H";
}

/**
 * @brief Get the Player object
 * 
 * @return Player 
 */
Player Game :: getPlayer(){
  return player;
}
