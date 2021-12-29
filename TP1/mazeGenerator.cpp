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
    int rows, cols, nRobots, nPosts, playerPosX, playerPosY;
    int tmp = n;
    
    char *fileName = (char*) malloc(12*sizeof(char));

    srand (time(NULL));

    for (int k = 0; k < n; k++, tmp--){
        sprintf(fileName, "MAZE_%02d.txt", tmp+1);
        FILE* f = fopen(fileName, "w");
        
        rows = ((rand() % 20) + 10);    // # of rows ranges from 10 to 30
        cols = ((rand() % 20) + 10);    // # of cols ranges from 10 to 30
        //nRobots = ((rand() % 4) + 5);   // # of robots ranges from 5 to 9
        nRobots = (ceil(sqrt(rows*cols))/2);
        nPosts = ceil(sqrt(rows*cols));

        playerPosX = ((rand() % (cols - 2)) + 1);   
        playerPosY = ((rand() % (rows - 2)) + 1);   
        
        fprintf (f, "%d x %d\n", rows, cols);
        //fprintf (f, "Number of robots: %d\nNumber of posts: %d\nplayerPosX: %d\nplayerPosY: %d\n", nRobots, nPosts, playerPosX, playerPosY);
        
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (i == 0 || i == rows - 1 || j == 0 || j == cols-1)           // generates the grid    
                    fprintf(f, "*");
                else if (i == playerPosY && j == playerPosX)                    // generates the player
                    fprintf(f, "H");
                else if ((rand() % (cols*rows)) < nRobots){                     // generates the robots
                    fprintf(f, "R");
                    nRobots--;
                }
                else if ((rand() %  (cols*rows)) < nPosts){                   // generates the posts
                    fprintf(f, "*");
                    nPosts--;
                }                                       
                
                else   
                    fprintf(f, " ");
            
            }
            fprintf(f, "\n");
        } 
        fclose(f);
    }

}

int main(){
    int numbOfMazes;
    cout << "How many mazes do you want to generate: ";
    cin >> numbOfMazes;
    generateMazes(numbOfMazes);
    return 0;
}