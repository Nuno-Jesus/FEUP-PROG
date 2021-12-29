// T09_G02
#include "Highscores.hpp"

#define FIRST_DIGIT_PLACE 22

/**
 * \brief Sorting algorithm
 * \param winners Vector to be sorted
 */
void Highscores :: bubbleSort(){
  for (unsigned int i = 0; i < winners.size(); i++){
    for (unsigned int j = 0; j < winners.size() - i - 1; j++){
      if(winners.at(j).getTime() > winners.at(j + 1).getTime())
        swap(winners.at(j), winners.at(j + 1));
      }
  }

  return;
}

/**
 * \brief Auxiliar function of bubble sorting
 * \param w1 Struct to be swapped
 * \param w2 Struct to be swapped
 */
void Highscores :: swap (Winners &w1, Winners &w2){
  Winners tmp = w1;
  w1 = w2;
  w2 = tmp;

  return;
}

/**
 * \brief Adds a new winner into the highscores
 * \param w Winners to be added
 */
void Highscores :: addWinner(const Winners w){
  winners.push_back(w);
}

/**
 * \brief Reads info from the file
 * \param f File to be checked
 */
void Highscores :: readWinners(fstream &f){
  Winners newWinner;
  string trash;

  string fName;
  string sName;
  int time;

  /* Reads the first two lines of the file and ignores it*/
  getline(f, trash, '\n');
  getline(f, trash, '\n');
  
  while(f >> fName >> sName >> time){
    newWinner = Winners(fName, sName, time);
    /* Ignores the rest of the line */
    getline(f, trash, '\n');    
    
    /* Inserts info from the file into the vector */
    winners.push_back(newWinner);  
  }
}

/**
 * \brief Write info to the file
 * \param f File to be written on
 */
void Highscores :: writeWinners(fstream &f){
    string fullName;
  
    for(unsigned int  i = 0; i < winners.size(); i++){    
      /* Write info from the vector into the file */
      f << winners.at(i).getFName() << " " << winners.at(i).getSName();   

      fullName = winners.at(i).getFName() + " " + winners.at(i).getSName();
      for(int i = 0; i < FIRST_DIGIT_PLACE - fullName.size(); i++){
        f << " ";
    }

    f << winners.at(i).getTime() << endl;
  }
}

/**
 * @brief Reads winners from a file and displays it onto the screen
 * @param filename filename
 */
void Highscores :: displayWinners(const string filename){
  char c;

  fstream winnersFile;
  winnersFile.open(filename);
  string line;

  if (fileIsEmpty(winnersFile)){
    cout << "\n\t----- FILE IS EMPTY. THERE ARE NO WINNERS. -----\n\n";
    return;
  }

  while(getline(winnersFile, line, '\n'))
    cout << line << endl;

  cout << '\n';

  while(1){
    cout << "Press 'q' to go back to menu.\n";

    cin >> c;

    if(cin.fail() && cin.eof()){
      cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
      exit(EXIT_FAILURE);
    }

    c = toupper(c);

    if(c == 'Q'){
      break;
    }

    cin.ignore(10000, '\n');
  }
}

/**
 * \brief Builds the name of the file containing the maze to be read, by asking the
 * user for the maze number.
 * \param fileName Place where the fileName will be stored
 * \param mazeN Variable to store the maze number for winners file
 * \return Returns true for error (user input = 0), false otherwise
*/
bool Highscores :: buildFileWinnersName(string &fileName, int &mazeN){
  int mazeNumber = 1;

  string number;
  fstream mazeFile;
  
  while(1){
    cout << "Maze number (0 to go back to menu): ";

    if(cin.fail() && cin.eof()){
      cout << "\n\t----- CTRL-Z/D DETECTED. ABORTING... -----\n\n";
      exit(EXIT_FAILURE);
    }

    /* Verifies if the digit input was a number */
    if(!isdigit(cin.peek())){
      cin.ignore(10000, '\n');
      cout << "\n\t----- INVALID INPUT: INSERT A NUMBER -----\n\n";
      continue;
    }

    cin >> mazeNumber;
    mazeN = mazeNumber;

    /* User input = 0 -> return to menu */
    if(mazeNumber == 0){
      return true;
    }

    else if(mazeNumber > 0){
      number = to_string(mazeNumber);

      if(mazeNumber < 10)
        fileName = "MAZE_0" + number + "_WINNERS.txt";

      else 
        fileName = "MAZE_" + number +  "_WINNERS.txt";
      
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

/** \brief Checks if a file is empty 
 * \param f File stream that opened the file to check
 * \return Returns true if the file is empty, false otherwise
*/
bool Highscores :: fileIsEmpty(fstream &f){
  return (f.peek() == EOF);
}
