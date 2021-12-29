//T09_G02

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

#define MAX_NAME_LENGTH 15
#define FIRST_DIGIT_PLACE 22

// STRUCTS ARE CREATED HERE
typedef enum moves_ {
  MOVE_LEFT_UP, MOVE_LEFT, MOVE_LEFT_DOWN, 
  STAY, MOVE_UP, MOVE_DOWN, MOVE_RIGHT_UP, 
  MOVE_RIGHT, MOVE_RIGHT_DOWN, INVALID
} Move;

typedef struct player_{
  int x;                // Player X position
  int y;                // Player Y position
  bool wasEletrocuted;  // True if player has hit a fence or a post
  bool wasRobotKilled;  // True if player has been killed by a robot
  bool hasWon;          // True if player has won the game
} Player;

typedef struct robot_{
  int id;               // Robot ID
  int x, y;             // Robot X and Y coordinates
  bool isStuck;         // True if the robot has hit anything but the player
} Robot;

typedef struct winner_{
  string fName;         // Contains player's first name
  string sName;         // Contains player's second name
  int time;             // Time that it took the player to complete the game
} Winner;

// FUNCTION HEADERS

/**
 * \brief Moves the robots one step closet to the player
 * 
 * \param mazeNumber Selected maze number
 * \param winnersTime Time that the player spent playing
 * \param errorOcurred Whether the loop terminated abnormally or not
 * \return bool value (true if player won)
 */
bool play_game(int &mazeNumber, int &winnersTime, bool &errorOcurred);

/**
 * \brief Checks whether or not the game is over
 * 
 * \param player Struct with player info 
 * \param robots Robots struct vector
 * \return bool value (true if the game is over)
 */
bool check_game_over(Player &player, const vector<Robot> robots);

/**
 * \brief Moves the player according to the selected move
 * 
 * \param maze Maze 
 * \param rows # of rows
 * \param cols # of columns
 * \param player Struct with player info 
 * \param move Enum type with the selected move
 * \return Enum type value
 */
Move move_player(char *maze, const int rows, const int cols, Player &player, const Move move);

/**
 * \brief Reads which move the player choose
 * 
 * \return Enum type value with the selected movement
 */
Move get_move();

/**
 * \brief Moves the robots one step closet to the player
 * 
 * \param robots Robots struct vector
 * \param maze Maze 
 * \param player Struct with player info 
 * \param cols # of columns
 */
void move_robots(vector<Robot> &robots, char* maze, Player &player, const int cols);

/**
 * \brief Reads the maze to play on from a file
 * 
 * \param fileName Name of the file to be opened
 * \param maze Array where the maze will be stored on
 * \param rows Rows of the maze
 * \param cols Columns of the maze
 * \param player Struct where the player position will be stored
 * \param robots Vector where all the robots positions will be stored
 */
void read_maze(char* fileName, char* maze, int &rows, int &cols, Player &player, vector <Robot> &robots);


/**
 * \brief Checks whether or not a file is emty
 * 
 * \param f File to be checked
 * \return bool value (true if the file is empty)
 */
bool fileIsEmpty(fstream &f);

/**
 * \brief Reads info from the file
 * 
 * \param f File to be checked
 * \param winners Vector where info will be stored at
 */
void read_winners(fstream &f, vector<Winner> &winners);

/**
 * \brief Write info to the file
 * 
 * \param f File to be written on
 * \param winners Vector with info about players and time
 */
void write_winners(fstream &f, const vector<Winner> winners);

/**
 * \brief Auxiliar function of bubble sorting
 * 
 * \param w1 Struct to be swapped
 * \param w2 Struct to be swapped
 */
void swap(Winner &w1, Winner &w2);

/**
 * \brief Sorting algorithm
 * 
 * \param winners Vector to be sorted
 */
void bubbleSort(vector<Winner> &winners);

/**
 * \brief Displays the maze on the screen
 * 
 * \param maze Maze to be displayed
 * \param cols # of columns
 * \param rows # of rows
 */
void print_maze(char *maze, const int cols, const int rows);

/**
 * \brief Displays possible moves on the screen
 * 
 */
void print_possible_moves();

/**
 * \brief Displays the menu on the screen
 * 
 */
void print_menu();

/**
 * \brief Displays the rules on the screen
 * 
 */
void print_rules();

/**
 * \brief Simulates a CTRL+L in the terminal
 */
void clearScreen();



int main(){
  int mazeNumber = 1;
  bool gameHasBeenPlayed = false, playerHasWon = false, errorOcurred = false;
  
  char winnersFileName[50], playerName[16];
  char op = '\n';
  
  Winner newWinner;
  vector <Winner> winners;

  fstream winnersFile;

  do{
    print_menu();
    cin >> op;
    
    if(isdigit(op)){
      switch(op){
        case '0': 
          cout << "Now exiting..." << endl;
          return 0;

        case '1':
          print_rules();
          break;

        case '2':
          cin.ignore(10000, '\n');
          
          playerHasWon = play_game(mazeNumber, newWinner.time, errorOcurred);
          
          if(!errorOcurred)
            gameHasBeenPlayed = true;

          break;

        default:
          clearScreen();
          cout << "\n\t----- INVALID INPUT: OUT OF BOUNDS -----\n\n";
          
          break;
      }
    }

    else{
      clearScreen();
      cout << "\n\t----- INVALID INPUT: NOT A DIGIT -----\n\n";

      continue;
    }

  }while(op != 0 && !gameHasBeenPlayed && errorOcurred);

  if(playerHasWon){
    cout << "\n\t----- CONGRATULATIONS! ALL ROBOTS WERE DESTROYED! -----\n\n";
    cout << "Your time: " << newWinner.time <<" seconds" << endl << endl;
    
    while(1){
      cout << "Your first and last name (max 15 characters): ";
      cin.get(playerName, 15);

      string playerNameStr = playerName;
      if(playerNameStr.find(" ") == -1){
        cin.ignore(10000, '\n');
        cout << "\n\t----- MUST HAVE TWO NAMES -----\n\n";
        continue;
      }

      istringstream instr(playerNameStr);
      instr >> newWinner.fName >> newWinner.sName;
      
      break;
    }
 
    winners.push_back(newWinner);                                                 // PUTS THE MOST RECENT WINNER IN THE VECTOR

    sprintf(winnersFileName, "MAZE_%02d_WINNERS.txt", mazeNumber);                
    winnersFile.open(winnersFileName);

    if(!winnersFile.is_open()){
      winnersFile.open(winnersFileName, ios::out);

      if(!winnersFile.is_open()){
        cerr << "\n\t----- FATAL ERROR: UNABLE TO CREATE / OPEN: " << winnersFileName << " -----\n\n";
        exit(EXIT_FAILURE);
      }
    }  

    if(fileIsEmpty(winnersFile)){
      winnersFile.clear();                                                        // CLEAR ERROR FLAGS

      winnersFile << "Player               Time" << endl;
      winnersFile << "-------------------------" << endl;
      
      write_winners(winnersFile, winners);                                        // WRITES THE ONLY WINNER
    }

    else{
      read_winners(winnersFile, winners);                                         // READS THE MAZE_XX_WINNERS.TXT FILE AND GETS THE SCORES
      winnersFile.close();

      bubbleSort(winners);
      
      winnersFile.open(winnersFileName, ios::out | ios::trunc);                   // OPENS THE FILE AGAIN WITH IOS::TRUNC SO WE CAN WRITE OVER IT AGAIN

      winnersFile << "Player               Time" << endl;
      winnersFile << "-------------------------" << endl;

      write_winners(winnersFile, winners);                                        // WRITES THE SORTED WINNER VECTOR INTO THE FILE
    }
    
    winnersFile.close();

    cout << "\n\t----- YOUR NAME HAS BEEN REGISTERED -----\n\n";
  }

  return 0;
}

bool play_game(int &mazeNumber, int &winnersTime, bool &errorOcurred){
  int rows, cols;

  char fileName[14];
  char *maze = (char*) malloc(1000 * sizeof(char));
  
  bool gameIsOver = false;

  Move move = INVALID;
  Player player;

  vector<Robot> robots;

  if(maze == nullptr){
    perror("\n\tERROR IN malloc():");
    exit(EXIT_FAILURE);
  }

  while(mazeNumber != 0){
    cout << "Maze number: ";

    if(!isdigit(cin.peek())){
      cin.ignore(10000, '\n');
      cout << "\n\t----- INVALID INPUT: INSERT A NUMBER -----\n\n";
      continue;
    }

    cin >> mazeNumber;

    if(mazeNumber == 0){
      errorOcurred = true;
      return false;
    }

    else if(mazeNumber > 0){                                                // IF THE INPUT FOR THE MAZENUMBER IS NON-NEGATIVE AND NON-ZERO
      sprintf(fileName, "MAZE_%02d.txt", mazeNumber);                       // BUIDLS THE FILE NAME
      read_maze(fileName, maze, rows, cols, player, robots);                // READS MAZE FROM THE FILE
      break;
    }
  }

  clearScreen();                                                            // CLEAR TERMINAL
  
  steady_clock counter;                                                     // INICIATES THE TIMER
  auto start = counter.now();

  print_possible_moves();
  while(!gameIsOver){
    print_maze(maze, cols, rows);

    do{
      if((move = get_move()) == INVALID){                                   // GETS A VALID INPUT FOR THE PLAYER'S MOVE
        cout << "\n\t----- INVALID MOVE: NOT A VALID LETTER -----\n\n";
        continue;
      }
      
      if((move = move_player(maze, rows, cols, player, move)) == INVALID){  // IF THE NEXT POSITION DOESN'T HAVE A ROBOT PILE, THE PLAYER CHANGES POSITION
        cout << "\n\t----- INVALID MOVE: ROBOT PILE AHEAD -----\n\n";
      }

    
    }while(move == INVALID);                                                // REPEATS THE CICLE UNTIL A VALID INPUT/MOVE IS GIVEN

    move_robots(robots, maze, player, cols);                                // MOVES THE ROBOTS TOWARDS THE PLAYER, ACCORDING TO THE PLAYER'S COORDINATES
    gameIsOver = check_game_over(player, robots);

    
    if(!gameIsOver)                                                         // CLEAR THE TERMINAL
      clearScreen();
  }
  auto end = counter.now();
  winnersTime = (int)static_cast<duration<double>>(end - start).count();    //CALCULATING THE ELAPSED TIME

  print_maze(maze, cols, rows);

  return player.hasWon;
}

bool check_game_over(Player &player, const vector<Robot> robots){
  if(player.wasEletrocuted){
    cout << "\n\t----- GAME OVER: YOU HAVE BEEN ELETROCUTED! -----\n\n";
    return true;
  }

  else if(player.wasRobotKilled){
    cout << "\n\t----- GAME OVER: A ROBOT KILLED YOU! -----\n\n";
    return true;
  }
  
  for(size_t i = 0; i < robots.size(); i++){
    if(!robots[i].isStuck)
      return false;
  }

  player.hasWon = true;
  return true;
}

Move move_player(char *maze, const int rows, const int cols, Player &player, const Move move){
  int deltaX = 0, deltaY = 0;
  int newX, newY;
  
  switch(move){
    //Upper left diagonal
    case MOVE_LEFT_UP:
      deltaX--;
      deltaY--;
      break;

    //Leftwards
    case MOVE_LEFT:
      deltaX--;
      break;

    //Lower left diagonal
    case MOVE_LEFT_DOWN:
      deltaX--;
      deltaY++;
      break;

    //Stay in position
    case STAY:
      deltaX = deltaY = 0;
      break;

    //Upwards
    case MOVE_UP:
      deltaY--;
      break;

    //Downwards
    case MOVE_DOWN:
      deltaY++;
      break;

    //Upper right diagonal
    case MOVE_RIGHT_UP:
      deltaX++;
      deltaY--;
      break;

    //Rightwards
    case MOVE_RIGHT:
      deltaX++;
      break;

    //Lower right diagonal
    case MOVE_RIGHT_DOWN:
      deltaX++;
      deltaY++;
      break;

    default:
      break;
  }

  newX = player.x + deltaX;                 // NEW PLAYER X COORDINATE
  newY = player.y + deltaY;                 // NEW PLAYER Y COORDINATE

  if(maze[newY * cols + newX] == 'r'){      // IF THE PLAYER TRIES TO MOVE TO A ROBOT PILE
    return INVALID;
  }

  else if(maze[newY * cols + newX] == 'R'){ // IF THE PLAYER TRIES TOWARDS A ROBOT
    player.wasRobotKilled = true;
  }

  else if(maze[newY * cols + newX] == '*'){ // IF THE PLAYER TRIES TOWARDS A FENCE OR A POST
    player.wasEletrocuted = true;
  }

  maze[player.y * cols + player.x] = ' ';   // IF THE CELL IS EMPTY
  player.y += deltaY;
  player.x += deltaX;

  if(player.wasEletrocuted || player.wasRobotKilled) 
    maze[player.y * cols + player.x] = 'h'; // IF THE PLAYER WAS KILLED, ITS CHARACTER CHANGES FROM 'H' TO 'h'

  else  
    maze[player.y * cols + player.x] = 'H'; 

  return STAY;
}

Move get_move(){
  char move;
  
  cout << "Choose your movement: "; 
  cin >> move;
  cin.ignore(10000, '\n');         // IGNORES \n CHARACTER
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

void move_robots(vector<Robot> &robots, char* maze, Player &player, const int cols){
  int deltaX = 0, deltaY = 0;
  int newX, newY;
  
  for(size_t i = 0; i < robots.size(); i++){
    if(!robots[i].isStuck){
      if(robots[i].x < player.x)                    // ROBOTS MOVES ONE STEP CLOSER TO THE PLAYER
        deltaX = 1;

      else if(robots[i].x > player.x)               // ROBOTS MOVES ONE STEP CLOSER TO THE PLAYER
        deltaX = -1;

      if(robots[i].y < player.y)                    // ROBOTS MOVES ONE STEP CLOSER TO THE PLAYER
        deltaY = 1;

      else if(robots[i].y > player.y)               // ROBOTS MOVES ONE STEP CLOSER TO THE PLAYER
        deltaY = -1;

      newX = robots[i].x + deltaX;                  // NEW ROBOT X COORDINATE
      newY = robots[i].y + deltaY;                  // NEW ROBOT Y COORDINATE

      maze[robots[i].y * cols + robots[i].x] = ' '; // CLEARS THE CURRENT CELL
    
      if(maze[newY * cols + newX] == 'H'){          // IF THE ROBOT TRIES TO MOVE TOWARDS THE PLAYER
        maze[newY * cols + newX] = 'h';             // CHANGE PLAYER CHARACTER TO 'h'
        player.wasRobotKilled = true;               // PLAYER IS DEAD
      }

      else if(maze[newY * cols + newX] == ' '){     // IF THE NEW CELL IS EMPTY
        maze[newY * cols + newX] = 'R';
      }

      else if(maze[newY * cols + newX] == 'R'){     // IF THE ROBOT TRIES TO MOVE TOWARDS ANOTHER ROBOT
        robots[i].isStuck = true;                   // ROBOT IS STUCK 

        for(size_t k = 0; k < robots.size(); k++){
          if(newX == robots[k].x && newY == robots[k].y){   // LOOKS FOR THE ROBOT THAT HIT THE CURRENT ROBOT
            robots[k].isStuck = true;                       // ROBOT 2 IS ALSO STUCK
            
            break;
          }
        }

        maze[newY * cols + newX] = 'r';              // CHANGES ROBOT CHARACTER FROM 'R' TO 'r'
      }

      else{
        maze[newY * cols + newX] = 'r';             // IF NEW CELL IS A ROBOT PILE OR A FENCE
        robots[i].isStuck = true;                   // ROBOT IS STUCK
      }

      robots[i].x = newX;                           // NEW ROBOT X COORDINATE
      robots[i].y = newY;                           // NEW ROBOT Y COORDINATE

      deltaX = deltaY = 0;
    }
  } 
}

void read_maze(char* fileName, char* maze, int &rows, int &cols, Player &player, vector <Robot> &robots){
  char c;
  int i = 0, robotID = 1;
  Robot r;
  
  FILE* f = fopen(fileName, "r");
  if(f != nullptr){
    fscanf(f, "%d x %d\n", &rows, &cols);     // READS THE FIRST LINE OF THE LINE CONTAING INFO ABOUT COLS AND ROWS

    while((c = getc(f)) != EOF){              // WHILE IT DOES NOT REACH THE END OF THE FILE
      if(c != '\n' && c != '\r'){             // IF CHARACTER IS NOT NEW LINE CHARACTER OR RETURN CARRY CHARACTER
        maze[i] = c;

        if(c == 'H'){                         // IF THE CHARACTER IS A PLAYER, FILL PLAYER STRUCT WITH INFO
          player.x = i % cols;
          player.y = i / cols;
          player.wasEletrocuted = false;
          player.wasRobotKilled = false;
          player.hasWon = false;
        }

        else if(c == 'R'){                    // IF THE CHARACTER IS A ROBOT, FILL ROBOT VECTOR WITH INFO
          r.id = robotID;
          r.x = i % cols;
          r.y = i / cols;
          r.isStuck = false;
          
          robots.push_back(r);
          robotID++;
        }

        i++;
      }
    }
  }

  else{
    cout << "\n\t ERROR: FILE HAS NOT BEEN FOUND\n\n";
    exit(EXIT_FAILURE);
  }

  fclose(f);
}


/***************************** FILE OPERATIONS *******************************/
bool fileIsEmpty(fstream &f){
  return (f.peek() == EOF);
}

void read_winners(fstream &f, vector<Winner> &winners){
  Winner winner;
  string trash;

  // READS THE FIRST TWO LINES OF THE FILE AND IGNORES IT
  getline(f, trash, '\n');
  getline(f, trash, '\n');
  
  while(f >> winner.fName >> winner.sName >> winner.time){
    getline(f, trash, '\n');    // IGNORES THE REST OF THE LINE
    winners.push_back(winner);  // INSERTS INFO FROM THE FILE INTO THE VECTOR
  }
}

void write_winners(fstream &f, const vector<Winner> winners){
  string fullName;
  
  for(size_t i = 0; i < winners.size(); i++){    
    f << winners[i].fName << " " << winners[i].sName;   // WRITES INFO FROM THE VECTOR INTO THE FILE

    fullName = winners[i].fName + " " + winners[i].sName;
    for(int i = 0; i < FIRST_DIGIT_PLACE - fullName.size(); i++){
      f << " ";
    }

    f << winners[i].time << endl;
  } 
}


/***************************** BUBBLE SORT ALGORITHM *******************************/
void swap (Winner &w1, Winner &w2){
  Winner tmp = w1;
  w1 = w2;
  w2 = tmp;
  return;
}

void bubbleSort(vector<Winner> &winners){
  for (size_t i = 0; i < winners.size(); i++)
    for (size_t j = 0; j < winners.size() - i - 1; j++){
      if(winners[j].time > winners[j + 1].time)
        swap(winners[j], winners[j + 1]);
      }
  return;
}


/***************************** CONSOLE PRINTS *******************************/
void print_maze(char *maze, const int cols, const int rows){
  for(int i = 0; i < cols * rows; i++){
    cout << maze[i];

    if((i + 1) % cols == 0)
      cout << endl;
  }

  cout << endl;
}

void print_possible_moves(){
  cout << "Possible moves:\n";
  cout << " -----------------" << endl;
  cout << "|     |     |     |         Q -> Left Up\n";
  cout << "|  Q  |  W  |  E  |         W -> Up\n";
  cout << "|     |     |     |         E -> Right Up\n";
  cout << " -----------------" << endl;
  cout << "|     |     |     |         A -> Left\n";
  cout << "|  A  |  S  |  D  |         S -> Stay\n";
  cout << "|     |     |     |         D -> Right\n";
  cout << " -----------------" << endl;
  cout << "|     |     |     |         Z -> Left Down\n";
  cout << "|  Z  |  X  |  C  |         X -> Down\n";
  cout << "|     |     |     |         C -> Right Down\n";
  cout << " -----------------" << endl;
  cout << endl;
}

void print_menu(){
  cout << endl;
  cout << "\t0101101  0101101 110101  0101101 0101101     0101101 0101101 0     1 0101101" << endl;
  cout << "\t1      0 0     1 0     1 0     1    0        0       0     1 1 0 1 0 0      " << endl;
  cout << "\t0101101  0     1 110110  0     1    0        0  1101 0101101 0  0  0 1101   " << endl;
  cout << "\t0     1  0     1 0     1 0     1    1        0     1 0     1 0     1 0      " << endl;
  cout << "\t1      0 0101101 110100  0101101    0        0101101 0     1 0     1 0101101" << endl;
  cout << endl;
  cout << "0) Exit" << endl;
  cout << "1) Rules" << endl;
  cout << "2) Play"  << endl;
  cout << "\nOption : ";
}

void print_rules(){
  char c;
  clearScreen();

  cout << "-------------------------------------------------" << endl;
  cout << "    0101101  0     1  0       0101101 0101101   |" << endl;
  cout << "    1      0 0     1  0       1       1         |" << endl;
  cout << "    0101101  0     1  1       1101    0101101   |" << endl;
  cout << "    0     1  0     1  0       0             1   |" << endl;
  cout << "    1      0 0101101  0101101 0101101 0101101   |" << endl;
  cout << "-------------------------------------------------" << endl;

  cout << endl;

  cout << "--> You'll be placed in a maze made up of high-voltage fences, posts and robots that will try to destroy you.\n";
  cout << "--> If you touch the fences, posts or any of the robots, it's game over.\n";
  cout << "--> Robots are also destroyed when they touch the fences/posts or when they collide with each other\n";
  cout << "--> Every time you move in any direction, each robot will move one step closer to your cell\n";
  cout << "--> You win the game if you can make all the robots hit the maze or each other\n";
  cout << "--> Good luck and have fun!\n\n";
  
  while(1){
    cout << "Press 'q' to quit.\n";

    cin >> c;
    c = toupper(c);

    if(c == 'Q'){
      clearScreen();
      break;
    }
  }
}

void clearScreen(){
  cout << "\033[2J\033[H";
}
