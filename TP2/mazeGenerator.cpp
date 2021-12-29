//T09_G02
#include <iostream>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <cmath>

using namespace std;
/**
 * \brief Generates mazes and stores them in a .txt file
 * 
 * \param n Number of mazes to be generated
 */
void generateMazes (int n);


void generateMazes (int n){
  int rows, cols, nRobots, nPosts, playerPosX, playerPosY, nPostsEletr, nPostsNormal, nGates;

  int tmp = n;
  
  char *fileName = (char*) malloc(12*sizeof(char));
  bool hasGateOnTop = false;
  bool hasGateOnBottom = false;

  srand (time(NULL));

  for (int k = 0; k < n; k++, tmp--){
    sprintf(fileName, "MAZE_%02d.txt", tmp+1);
    FILE* f = fopen(fileName, "w");
    
    rows = ((rand() % 10) + 10);  // # of rows ranges from 10 to 30
    cols = 2 * rows;
    nRobots = (ceil(sqrt(rows*cols))/2);
    nPosts = ceil(2 * sqrt(rows*cols));
    nPostsEletr = ceil(nPosts * 0.25);
    nPostsNormal = nPosts - nPostsEletr;
    nGates = ceil((rows*cols) % 3 + 2);
    
    playerPosX = ((rand() % (cols - 2)) + 1);   
    playerPosY = ((rand() % (rows - 2)) + 1);   
    
    fprintf (f, "%d x %d\n", rows, cols);
    printf("Number of robots: %d\n", nRobots);
    printf("Number of posts: %d\n\t -Normal: %d\n\t -Eletrified: %d\n", nPosts, nPostsNormal, nPostsEletr);
    printf("Number of gates: %d\n", nGates);

    
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        
        if (i == 0)       // generates the grid  
        {
          if ((rand() % 12) < nGates && !hasGateOnTop && nGates > 0){
            fprintf(f, "O");
            nGates--;
            hasGateOnTop = true;
          }
          else
            fprintf(f, "*");
        }

        else if (i == rows - 1)    // generates the grid  
        {
          if ((rand() % 12) < nGates && !hasGateOnBottom && nGates > 0){
            fprintf(f, "O");
            nGates--;
            hasGateOnBottom = true;
          }
          else
            fprintf(f, "*");
        }

        else if (i == rows - 1)    // generates the grid  
        {
          if ((rand() % 12) < nGates && !hasGateOnBottom && nGates > 0){
            fprintf(f, "O");
            nGates--;
            hasGateOnBottom = true;
          }
          else
            fprintf(f, "*");
        }

        else if (j == 0 || j == cols - 1)    // generates the grid  
        {
          if ((rand() % 12) < nGates && nGates > 0){
            fprintf(f, "O");
            nGates--;
            hasGateOnBottom = true;
          }
          else
            fprintf(f, "*");
        }

        
        
        else if (i == playerPosY && j == playerPosX)          // generates the player
          fprintf(f, "H");
           

        else if ((rand() % (cols*rows-5)) < nRobots){           // generates the robots
          fprintf(f, "R");
          nRobots--;
        }
         
        else if ((rand() %  (cols*rows-5)) < nPostsNormal){        // generates the posts
          fprintf(f, "+");
          nPostsNormal--;
        }
        
        else if ((rand() %  (cols*rows-5)) < nPostsEletr){           // generates the posts
          fprintf(f, "*");
          nPostsEletr--;
        }                    
          
        else   
          fprintf(f, " ");
      }
      fprintf(f, "\n");
    } 
    
    
    
    fclose(f);
  }
  printf("Number of remaining robots : %d\n", nRobots);
  printf("Number of remaining normalPosts : %d\n", nPostsNormal);
  printf("Number of remaining eletricPosts : %d\n", nPostsEletr);
  printf("Number of remaining gates: %d\n", nGates);
}

int main(){
  int numbOfMazes;
  cout << "How many mazes do you want to generate: ";
  cin >> numbOfMazes;
  generateMazes(numbOfMazes);
  return 0;
}