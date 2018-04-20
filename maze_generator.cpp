// DaanyaMGA = Daanya's Maze Generator Algorithm

# include "DaanyaMGA.hpp"

// using namespace std;


DaanyaMGA::DaanyaMGA()
{
}

vector<Direction> DaanyaMGA::possibleDirections(Maze& maze)
{
  vector<Direction> possible;
  
  if (currentCell_y - 1 >= 0) {
    // ensures next cell being tested is within maze confines
    // next part checks that next cell has all 4 walls drawn
    if (maze.wallExists(currentCell_x, currentCell_y-1, Direction::up)
        && maze.wallExists(currentCell_x, currentCell_y-1, Direction::right)
        && maze.wallExists(currentCell_x, currentCell_y-1, Direction::down)
        && maze.wallExists(currentCell_x, currentCell_y-1, Direction::left)){
      possible.push_back(Direction::up);
    }
  }
  if (currentCell_x + 1 < maze.getWidth()) {
    if (maze.wallExists(currentCell_x+1, currentCell_y, Direction::up)
        && maze.wallExists(currentCell_x+1, currentCell_y, Direction::right)
        && maze.wallExists(currentCell_x+1, currentCell_y, Direction::down)
        && maze.wallExists(currentCell_x+1, currentCell_y, Direction::left)){
      possible.push_back(Direction::right);
    }
  }
  if (currentCell_y + 1 < maze.getHeight()) {
    if (maze.wallExists(currentCell_x, currentCell_y+1, Direction::up)
        && maze.wallExists(currentCell_x, currentCell_y+1, Direction::right)
        && maze.wallExists(currentCell_x, currentCell_y+1, Direction::down)
        && maze.wallExists(currentCell_x, currentCell_y+1, Direction::left)){
      possible.push_back(Direction::down);
    }
  }
  if (currentCell_x - 1 >= 0) {
    if (maze.wallExists(currentCell_x-1, currentCell_y, Direction::up)
        && maze.wallExists(currentCell_x-1, currentCell_y, Direction::right)
        && maze.wallExists(currentCell_x-1, currentCell_y, Direction::down)
        && maze.wallExists(currentCell_x-1, currentCell_y, Direction::left)){
      possible.push_back(Direction::left);
    }
  }
 
  return possible;
}

void DaanyaMGA::move(Maze& maze)
{
  vector<Direction> possible = possibleDirections(maze);

  // to handle when algorithm hits dead end and needs to backtrack
  int count = 1; 
  while (possible.size() == 0
      && visited.size() < (maze.getWidth() * maze.getHeight())) {
    currentCell_x = get<0>(visited[visited.size()-count]);
    currentCell_y = get<1>(visited[visited.size()-count]);
    possible = possibleDirections(maze);
    count ++;
  }

  // randomly picks which direction to go in next and keeps looking until
  // direction is valid, then removes wall in that direction 
  Direction d;
  int direction = 0;
  do{
    direction = distribution(engine);
    switch(direction){
      case 1: d = Direction::up; break;
      case 2: d = Direction::right; break;
      case 3: d = Direction::down; break;
      case 4: d = Direction::left; break;
    }
  } while (find(possible.begin(), possible.end(), d) == possible.end());
  maze.removeWall(currentCell_x, currentCell_y, d);

  // mark current cell as visited
  visited.push_back(make_tuple(currentCell_x, currentCell_y)); 

  // change current cell coordinates to new cell whose wall we just removed
  switch(direction){
    case 1: currentCell_y -= 1; break;
    case 2: currentCell_x += 1; break;
    case 3: currentCell_y += 1; break;
    case 4: currentCell_x -= 1; break;
  }
}

void DaanyaMGA::mainRecursive(Maze& maze)
{
  move(maze);
  if (visited.size() == (maze.getHeight() * maze.getWidth())) {
    return;
  } else {
    mainRecursive(maze);
  }
}

void DaanyaMGA::generateMaze(Maze& maze)
{
  maze.addAllWalls();
  currentCell_x = 0;
  currentCell_y = 0;
  visited.push_back(make_tuple(currentCell_x, currentCell_y));
  mainRecursive(maze);
}
