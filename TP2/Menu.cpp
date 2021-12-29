// T09_G02
#include "Menu.hpp"

using namespace std;
/***************************** CONSOLE PRINTS *******************************/

void displayPossibleMoves(){
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

void displayTitle(){
  cout << "\t0101101  0101101 110101  0101101 0101101     0101101 0101101 0     1 0101101   0       1  01010 " << endl;
  cout << "\t1      0 0     1 0     1 0     1    0        0       0     1 1 0 1 0 0          1     0  1     0" << endl;
  cout << "\t0101101  0     1 110110  0     1    0        0  1101 0101101 0  0  0 1101        0   1       10 " << endl;
  cout << "\t0     1  0     1 0     1 0     1    1        0     1 0     1 0     1 0            1 0      01   " << endl;
  cout << "\t1      0 0101101 110100  0101101    0        0101101 0     1 0     1 0101101       1     1010011" << endl;
  cout << endl;
}

void clearScreen(){
  cout << "\033[2J\033[H";
}

/******************************** RULES **********************************/

void displayRules(){
  char c;
  clearScreen();

  fstream rulesFile;
  rulesFile.open("RULES.txt");
  string line;

  if(!rulesFile.is_open()){
    cerr << "\n\t----- FATAL ERROR: COULD NOT FIND RULES.txt -----\n\n";
    exit(EXIT_FAILURE);
  }

  while(getline(rulesFile, line, '\n'))
    cout << line << endl;
  
  while(1){
    cout << "Press 'q' to go back to menu.\n";

    cin >> c;

    if(cin.fail() && cin.eof()){
      cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
      exit(EXIT_FAILURE);
    }
    
    c = toupper(c);

    if(c == 'Q'){
      clearScreen();
      break;
    }

    cin.ignore(10000, '\n');
  }
}


void displayLetter1(){
  cout << "\t0101101                                                                                         " << endl;
  cout << "\t1      0                                                                                        " << endl;
  cout << "\t0101101                                                                                         " << endl;
  cout << "\t0     1                                                                                         " << endl;
  cout << "\t1      0                                                                                        " << endl;
  cout << endl;
}

void displayLetter2(){
  cout << "\t         0101101                                                                                " << endl;
  cout << "\t         0     1                                                                                " << endl;
  cout << "\t         0     1                                                                                " << endl;
  cout << "\t         0     1                                                                                " << endl;
  cout << "\t         0101101                                                                                " << endl;
  cout << endl;
}

void displayLetter3(){
  cout << "\t                 110101                                                                         " << endl;
  cout << "\t                 0     1                                                                        " << endl;
  cout << "\t                 110110                                                                         " << endl;
  cout << "\t                 0     1                                                                        " << endl;
  cout << "\t                 110100                                                                         " << endl;
  cout << endl;
}

void displayLetter4(){
  cout << "\t                         0101101                                                                " << endl;
  cout << "\t                         0     1                                                                " << endl;
  cout << "\t                         0     1                                                                " << endl;
  cout << "\t                         0     1                                                                " << endl;
  cout << "\t                         0101101                                                                " << endl;
  cout << endl;
}

void displayLetter5(){
  cout << "\t                                 0101101                                                        " << endl;
  cout << "\t                                    0                                                           " << endl;
  cout << "\t                                    0                                                           " << endl;
  cout << "\t                                    1                                                           " << endl;
  cout << "\t                                    0                                                           " << endl;
  cout << endl;
}

void displayLetter6(){
  cout << "\t                                             0101101                                            " << endl;
  cout << "\t                                             0                                                  " << endl;
  cout << "\t                                             0  1101                                            " << endl;
  cout << "\t                                             0     1                                            " << endl;
  cout << "\t                                             0101101                                            " << endl;
  cout << endl;
}

void displayLetter7(){
  cout << "\t                                                     0101101                                    " << endl;
  cout << "\t                                                     0     1                                    " << endl;
  cout << "\t                                                     0101101                                    " << endl;
  cout << "\t                                                     0     1                                    " << endl;
  cout << "\t                                                     0     1                                    " << endl;
  cout << endl;
}

void displayLetter8(){
  cout << "\t                                                             0     1                            " << endl;
  cout << "\t                                                             1 0 1 0                            " << endl;
  cout << "\t                                                             0  0  0                            " << endl;
  cout << "\t                                                             0     1                            " << endl;
  cout << "\t                                                             0     1                            " << endl;
  cout << endl;
}

void displayLetter9(){
  cout << "\t                                                                      0101101                   " << endl;
  cout << "\t                                                                      0                         " << endl;
  cout << "\t                                                                      1101                      " << endl;
  cout << "\t                                                                      0                         " << endl;
  cout << "\t                                                                      0101101                   " << endl;
  cout << endl;
}

void displayLetter10(){
  cout << "\t                                                                               0       1        " << endl;
  cout << "\t                                                                                1     0         " << endl;
  cout << "\t                                                                                 0   1          " << endl;
  cout << "\t                                                                                  1 0           " << endl;
  cout << "\t                                                                                   1            " << endl;
  cout << endl;
}

void displayLetter11(){
  cout << "\t                                                                                          01010 " << endl;
  cout << "\t                                                                                         1     0" << endl;
  cout << "\t                                                                                             10 " << endl;
  cout << "\t                                                                                           01   " << endl;
  cout << "\t                                                                                         1010011" << endl;
  cout << endl;
}

void displayMenu(){
  cout << "0) Exit" << endl;
  cout << "1) Rules" << endl;
  cout << "2) Play"  << endl;
  cout << "3) Highscores" << endl;
  cout << "\nOption : ";
}
