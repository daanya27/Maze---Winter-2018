// DaanyaMSA = Daanya's Maze Solver Algorithm

# include "DaanyaMSA.hpp"

using namespace std;


DaanyaMSA::DaanyaMSA()
{
}

vector<Direction> DaanyaMSA::possibleDirections(const Maze& maze,
                                                MazeSolution& mazeSolution)
{
  vector<Direction> possible;
  vector<Direction> directions = {Direction::up, Direction::right,
                                  Direction::down, Direction::left};
  Direction currentDir;
  pair<int, int> nextCell;
  
  for (int dir = 0; dir < 4; dir++) {
    currentDir = directions[dir]; // to iterate through directions
    switch(dir) {
      case 0: nextCell = make_pair(currentCell_x, currentCell_y - 1); break;
      case 1: nextCell = make_pair(currentCell_x + 1, currentCell_y); break;
      case 2: nextCell = make_pair(currentCell_x, currentCell_y + 1); break;
      case 3: nextCell = make_pair(currentCell_x - 1, currentCell_y); break;
    }
    if(!maze.wallExists(currentCell_x, currentCell_y, currentDir)
       && nextCell.first < maze.getWidth() && nextCell.first >= 0
       && nextCell.second < maze.getHeight() && nextCell.second >= 0
       && find(visited.begin(), visited.end(), nextCell) == visited.end()) {
      possible.push_back(currentDir);
    }
  }
  
  return possible;
}

void DaanyaMSA::trySolve(const Maze& maze, MazeSolution& mazeSolution)
{
  vector<Direction> possible = possibleDirections(maze, mazeSolution);
  
  while (possible.size() == 0
         && mazeSolution.getCells().size() <
         (maze.getWidth() * maze.getHeight())) {
    mazeSolution.backUp();
    currentCell_x = mazeSolution.getCurrentCell().first;
    currentCell_y = mazeSolution.getCurrentCell().second;
    possible = possibleDirections(maze, mazeSolution);
  }

  Direction dir = possible[0];
  if (!maze.wallExists(mazeSolution.getCurrentCell().first,
                       mazeSolution.getCurrentCell().second, dir)) {
    mazeSolution.extend(dir);
    visited.push_back(mazeSolution.getCurrentCell());
    currentCell_x = mazeSolution.getCurrentCell().first;
    currentCell_y = mazeSolution.getCurrentCell().second;
  }
}

void DaanyaMSA::mainRecursive(const Maze& maze, MazeSolution& mazeSolution)
{
  trySolve(maze, mazeSolution);
  if (mazeSolution.isComplete()) {
   return;
  } else {
   mainRecursive(maze, mazeSolution);
  }
}

void DaanyaMSA::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
  mazeSolution.restart();
  currentCell_x = 0;
  currentCell_y = 0; 
  mainRecursive(maze, mazeSolution);
}
                               
