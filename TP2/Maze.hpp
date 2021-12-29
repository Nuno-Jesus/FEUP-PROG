// T09_G02
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>

#include "Post.hpp"
#include "Gate.hpp"

using namespace std;


class Maze{
  public:
    Maze();
    Maze(unsigned int rows, unsigned int cols);

    void addPost(const Post post);
    void addGate(const Gate gate);
    void addElement(const char elem);
    void setElement(int pos, char c);

    unsigned int getRows() const;
    unsigned int getCols() const;
    unsigned int getNumPosts() const;
    unsigned int getNumGates() const;

    char getElement(unsigned int pos) const;
    Post getPost(unsigned int pos) const;
    Gate getGate(unsigned int pos) const;

  private:
    unsigned int rows;
    unsigned int cols;

    unsigned int numPosts;
    unsigned int numGates;

    vector<Post> posts;
    vector<Gate> gates;
    vector<char> mazeMap;
};

#endif