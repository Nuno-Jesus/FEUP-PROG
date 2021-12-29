FLAGS := -Wunused -Wall

all: robot post player maze gate game menu winners highscores link

robot: Robot.cpp	
	clang++ -c $(FLAGS) Robot.cpp

post: Post.cpp
	clang++ -c $(FLAGS) Post.cpp

player:	Player.cpp
	clang++ -c $(FLAGS) Player.cpp

maze:	Maze.cpp
	clang++ -c $(FLAGS) Maze.cpp

gate:	Gate.cpp
	clang++ -c $(FLAGS) Gate.cpp

game:	Game.cpp
	clang++ -c $(FLAGS) Game.cpp

menu: Menu.cpp
	clang++ -c $(FLAGS) Menu.cpp

winners: Winners.cpp
	clang++ -c $(FLAGS) Winners.cpp

highscores: Highscores.cpp
	clang++ -c $(FLAGS) Highscores.cpp

link:	Main.cpp Robot.o Post.o Player.o Maze.o Gate.o Game.o Menu.o Winners.o Highscores.o
	clang++ $(FLAGS) Main.cpp Robot.o Post.o Player.o Maze.o Gate.o Game.o Menu.o Winners.o Highscores.o

clean:
	rm Player.o
	rm Robot.o
	rm Post.o
	rm Gate.o
	rm Maze.o
	rm Game.o
	rm Menu.o
	rm Winners.o
	rm Highscores.o
	rm a.out


#SRC := $(wildcard *.cpp)
#OBJ := $(SRC:cpp=o)

#all: chase

#chase: $(OBJ) clang++ $(OBJ) -o chase

#$(OBJ): %.o: %.cpp clang++ -c $<

#clean: rm *.o