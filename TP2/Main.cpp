// T09_G02
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>

#include "Game.hpp"
#include "Maze.hpp"
#include "Robot.hpp"
#include "Player.hpp"
#include "Gate.hpp"
#include "Post.hpp"
#include "Menu.hpp"
#include "Winners.hpp"
#include "Highscores.hpp"

using namespace std;

// MACROS
#define MAX_NAME_LENGTH 15

//If defined, will display an animated intro in the beginning
#define DISPLAY_INTRO

typedef void (*letterFunction)();

/**
 * \brief Builds the name of the file containing the maze to be read, by asking the
 * user for the maze number.
 * 
 * \param fileName Place where the fileName will be stored
 * \param mazeNumber Variable to store the maze number for winners file
 * \return Returns true for error (user input = 0), false otherwise
*/
bool buildMazeFileName(string &fileName, int &mazeN);

/**
 * \brief This function makes use of the function clock() in a while loop
 * to create a delay as big as the one asked int the parameter.
 * \param sec Number of seconds (could be < 1.0) to keep the while loop running
*/
void delay(double sec);


/** \brief Displays information about the available user input for player in-game movement. */
void displayPossibleMoves();


/**
 * \brief Checks whether or not a file is emty
 * 
 * \param f File to be checked
 * \return bool value (true if the file is empty)
 */
bool fileIsEmpty(fstream &f);


int main(){
  char option;

  bool errorOcurred = false, gameHasBeenPlayed = false;
  int mazeNumber = 0;

  string fileName;
  
  /* Game object */
  Game game;
  /* Highscores object */
  Highscores scores;
  /* Winners object */
  Winners newWinner;

  char winnersFileName[50], playerName[16];
  
  /* Player info */
  string fName;
  string sName;
  double winTime;

  fstream winnersFile;

  #ifdef DISPLAY_INTRO
    letterFunction functions[] = {
      displayLetter1,
      displayLetter2,
      displayLetter3,
      displayLetter4,
      displayLetter5,
      displayLetter6,
      displayLetter7,
      displayLetter8,
      displayLetter9,
      displayLetter10,
      displayLetter11,
    };

    clearScreen();

    for(int i = 0; i < 11; i++){   
      functions[i]();
      delay(0.2);
      clearScreen();
    }

    clearScreen();
  #endif

  /* Game cicle */
  do{
    displayTitle();
    displayMenu();

    cin >> option;

    if(cin.fail() && cin.eof()){
      cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
      exit(EXIT_FAILURE);
    }
    
    /* Acts accordingly to the option selected above */
    if(isdigit(option)){
      switch(option){
        /* Exit */
        case '0': 
          cin.ignore(10000, '\n');
          cout << "Now exiting..." << endl;
          return 0;

        /* Rules */
        case '1':
          cin.ignore(10000, '\n');
          displayRules();
          break;

        /* Play */
        case '2':
          cin.ignore(10000, '\n');
          clearScreen();
          
          /* buildMazeFileName asks the user for a maze number and then tries to open said file, returns 1 if an error occured */
          errorOcurred = buildMazeFileName(fileName, mazeNumber); 
          if(errorOcurred){
            cout << "\n\t----- NUMBER 0 WAS INTRODUCED. GOING BACK TO MENU. -----\n\n";
            break;
          }

          /* Initializes the game */
          game = Game(fileName);                    

          /* Displays a matrix of possible moves to the user */
          displayPossibleMoves();

          /* Calls the game loop */
          winTime = game.play();
          gameHasBeenPlayed = true;

          break;

        /* Highscores */
        case '3':
          cin.ignore(10000, '\n');
          clearScreen();
          
          /* buildFileWinnersName asks the user for a maze number and then tries to open the correspondent highscores file, returns 1 if an error occured */
          errorOcurred = scores.buildFileWinnersName(fileName, mazeNumber);
          clearScreen();
          
          if(errorOcurred){
            cout << "\n\t----- NUMBER 0 WAS INTRODUCED. GOING BACK TO MENU. -----\n\n";
            break;
          }

          scores.displayWinners(fileName);
          clearScreen();

          break;

        default:
          cin.ignore(10000, '\n');
          clearScreen();
          cout << "\n\t----- INVALID INPUT: OUT OF BOUNDS -----\n\n";
          
          break;
      }
    }

    else{
      cin.ignore(10000, '\n');
      clearScreen();
      cout << "\n\t----- INVALID INPUT: NOT A DIGIT -----\n\n";

      continue;
    }

  }while(option != 0 && !gameHasBeenPlayed);

  Player p1 = game.getPlayer();

  /* p1.hasFoundGate() tells us whether the user has won the game or not */
  if(p1.hasFoundGate()){
    
    /* Displays the time the player took to win */
    cout << endl;
    cout << "Your time: " << winTime << " seconds" << endl;
    
    while(1){
      /* Asks for a name */
      cout << "Your first and last name (max 15 characters): ";
      
      /* Reads only a pre-defined number of caracters */
      cin.get(playerName, MAX_NAME_LENGTH);

      if(cin.fail() && cin.eof()){
        cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
        exit(EXIT_FAILURE);
      }

      string playerNameStr = playerName;
      /* If a whitespace wasn't found, that means the user didn't input two names */
      if(playerNameStr.find(" ") == -1){
        cin.ignore(10000, '\n');
        cout << "\n\t----- MUST HAVE TWO NAMES -----\n\n";
        continue;
      }

      istringstream instr(playerNameStr);
      instr >> fName >> sName;

      /* Creates a new player object with the new player's info */
      newWinner = Winners(fName, sName, round(winTime));
      
      break;
    }

    /* Pushes the most recent winner into the highscores */
    scores.addWinner(newWinner);                                               

    
    sprintf(winnersFileName, "MAZE_%02d_WINNERS.txt", mazeNumber);                
    winnersFile.open(winnersFileName);

    /* If the file wasn't created, creates a new one */
    if(!winnersFile.is_open()){
      winnersFile.open(winnersFileName, ios::out);

      /* Displays error message if an error occured while creating the file */
      if(!winnersFile.is_open()){
        cerr << "\n\t----- FATAL ERROR: UNABLE TO CREATE / OPEN: " << winnersFileName << " -----\n\n";
        exit(EXIT_FAILURE);
      }
    }  

    /* File exists, but is empty */
    if(fileIsEmpty(winnersFile)){
      
      /* Clear error flags */
      winnersFile.clear();                                                        

      /* Writes the header */
      winnersFile << "Player            -  Time" << endl;
      winnersFile << "-------------------------" << endl;
      
      /* Writes the only player in the file */
      scores.writeWinners(winnersFile);                                        
    }

    /* file exists and is NOT empty */
    else{
      /* Reads the MAZE_XX_WINNERS.TXT and gets the scores */
      scores.readWinners(winnersFile);                                         
      winnersFile.close();

      /* Sorts the highscores */
      scores.bubbleSort();                                                
      
      /* Opens the file again with IOS :: TRUNC so that we can write over it again */
      winnersFile.open(winnersFileName, ios::out | ios::trunc);                   

      /* Writes the header */
      winnersFile << "Player            -  Time" << endl;
      winnersFile << "-------------------------" << endl;

      /* Write the now sorted highscores in the file */
      scores.writeWinners(winnersFile);                                         
    }
    
    winnersFile.close();

    /* Displays a confirmation message */
    cout << "\n\t----- YOUR NAME HAS BEEN REGISTERED -----\n\n";
  }

  return 0;
}

/**************************** HELPER FUNCTIONS ****************************/

bool buildMazeFileName(string &fileName, int &mazeN){
  int mazeNumber = 1;

  string number;
  fstream mazeFile;
  
  while(1){
    cout << "Maze number (0 to go back to menu): ";

    /* Verifies if the stream input was a number */
    if(!isdigit(cin.peek())){
      cin.ignore(10000, '\n');
      cout << "\n\t----- INVALID INPUT: INSERT A NUMBER -----\n\n";
      continue;
    }

    cin >> mazeNumber;

    if(cin.fail() && cin.eof()){
      cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
      exit(EXIT_FAILURE);
    }

    mazeN = mazeNumber;

    /* User input = 0 -> return to menu */
    if(mazeNumber == 0){
      return true;
    }


    else if(mazeNumber > 0){
      number = to_string(mazeNumber);

      if(mazeNumber < 10)
        fileName = "MAZE_0" + number + ".txt";

      else 
        fileName = "MAZE_" + number + ".txt";
      
      /* Opens the file to check for its existence */
      mazeFile.open(fileName);
      
      /* If the file doesn't exist, user input will asked for again */
      if(!mazeFile.is_open()){
        cin.ignore(10000, '\n');
        cerr << "\n\t----- THE FILE " << fileName << " WAS NOT FOUND -----\n\n";
        continue;
      }

      mazeFile.close();
      
      break;
    }
  }

  return false;
  
}

void delay(double sec){
  clock_t start = clock();
  clock_t end = clock();

  double time = 0.0;
  
  while (time < sec){
    end = clock();
    time = (double) (end - start) / CLOCKS_PER_SEC;
  }     
}


bool fileIsEmpty(fstream &f){
  return (f.peek() == EOF);
}




