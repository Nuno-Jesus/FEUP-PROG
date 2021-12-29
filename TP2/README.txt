T09_02

Practical Work #2


GROUP MEMBERS:

- Carlos Verissimo
- Nuno Jesus


PROGRAM DEVELOPMENT:                    >> STATE

- Generate random mazes                 >> DONE
- Development  of classes and methods for:
    - Game                              >> DONE
    - Gate                              >> DONE
    - Highscores                        >> DONE
    - Menu                              >> DONE
    - Player                            >> DONE
    - Post                              >> DONE
    - Robot                             >> DONE
    - Winners                           >> DONE
- Development  of the game logic itself >> DONE
- Getting CTRL+D/Z to work              >> DONE


MAIN DIFFICULTIES:

- Nothing worth mentioning


USAGE:

- There are already 3 pre-generated mazes (1, 2 and 3). If you wish to play more mazes, compile mazeGenerator.cpp and 
input how many mazes you want to generate.
- There are two defines that are worth mentioning:
    - DEBUG, implemented on Game.cpp, prints some useful information used to ease the debug process
        >> By default, the code is commented.
    - INTRO, implemented on Main.cpp, can be used when the user wants to go straight into the game, skipping the intro
        >> By default, the code is NOT commented.
- Compilation is rather simple as a makefile was developed for that purpose.
    - Open the terminal
    - Run *make* or *make all*
    - Run *./a.out*
    - You can also run *make clean* to remove all the object files
- Exiting the game is also simple as you can run *CTRL+D/Z* at any point in the game or just exit the game on the main menu.
