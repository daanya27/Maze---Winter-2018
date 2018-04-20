// DaanyaMGA = Daanya's Maze Generator Algorithm

# ifndef DAANYAMGA_HPP
# define DAANYAMGA_HPP

# include "MazeGenerator.hpp"  // provided
# include "Maze.hpp"  // provided
# include <random>
# include <vector>

using namespace std;


class DaanyaMGA: public MazeGenerator  // MazeGenerator base class provided. DaanyaMGA creates maze gen. algorithm.
{
public: 
  /** Default constructor for maze generator
   */
  DaanyaMGA();

  /** Returns vector of possible paths given current cell and maze
   */
  vector<Direction> possibleDirections(Maze& maze);

  /** Handles navigating through the maze once initiated 
   */ 
  void move(Maze& maze);
  
  /** Recursive function that forks to either keep going or cutting 
      off program
   */
  void mainRecursive(Maze& maze);
  
  
  /** Built on mazeGenerator class virtual function, initates
      generation of random maze
   */
  void generateMaze(Maze& maze);
  

private:
  random_device device;     // random device built into class for easy access
  default_random_engine engine{device()};
  uniform_int_distribution<int> distribution{1,4};
  // dist 1,2,3,4 for up, right, down, left respectively 

  int currentCell_x;
  int currentCell_y;
  vector<tuple<int,int>> visited;
  // vector including cell coords that have been visited already
  
};

# endif // DAANYAMGA_HPP
