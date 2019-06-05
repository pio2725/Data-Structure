#pragma once
#include "PathfinderInterface.h"
#include <ctime>
#include <fstream>
#include <sstream>

const int TOTAL_CELL = 125;

class Pathfinder : public PathfinderInterface
{
public:
	Pathfinder();
	~Pathfinder();

	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
	
private:
	bool find_maze_path(int x, int y, int z);
	vector<string> solution;
	int maze_grid[5][5][5];
	int maze_temp[5][5][5];
	int format_maze[5][5][5];
};

