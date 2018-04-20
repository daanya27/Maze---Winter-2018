// DaanyaMSA = Daanya's Maze Solver Algorithm

# ifndef DAANYAMSA_HPP
# define DAANYAMSA_HPP

# include "MazeSolver.hpp"  // provided
# include "MazeSolution.hpp"  // provided
# include "Maze.hpp"  // provided
# include <vector>

using namespace std;

class DaanyaMSA: public MazeSolver  // MazeSolver base class provided. DaanyaMSA creates maze solving algorithm. 
{
public:
  /** Default constructor for maze solver
   */
  DaanyaMSA();
  
  /** Returns vector of possible Directions that solution can move in 
   */
  vector<Direction> possibleDirections(const Maze& maze,
                                       MazeSolution& mazeSolution);

  /** Trys next move in solution 
   */
  void trySolve(const Maze& maze, MazeSolution& mazeSolution);
  
  /** Handles moving solver until solution is reached
   */
  void mainRecursive(const Maze& maze, MazeSolution& mazeSolution); 

  /** Built on mazeSolver class virtual function, initiates
      solving algorithm in perfect maze
   */
  void solveMaze(const Maze& maze, MazeSolution& mazeSolution); 

private:
  int currentCell_x;
  int currentCell_y;
  vector<pair<int,int>> visited;
};

# endif // DAANYAMSA_HPP
