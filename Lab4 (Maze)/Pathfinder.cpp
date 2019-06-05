#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
	srand(time(NULL));

	//maze consists of all 1, if hasn't been imported
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				maze_grid[i][j][k] = 1;
			}
		}
	}
}

Pathfinder::~Pathfinder()
{
}

string Pathfinder::toString() const
{
	ostringstream os;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (k == 4)
				{
					os << maze_grid[i][j][k];
				}
				else
				{
					os << maze_grid[i][j][k] << " ";
				}
			}
			os << endl;
		}

		if (i != 4)
		{
			os << endl;
		}
	}
	return os.str();
}

void Pathfinder::createRandomMaze()
{
	int random_maze[5][5][5];
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; ++k)
			{
				maze_grid[i][j][k] = rand() % 2;
			}
		}
	}
	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}

bool Pathfinder::importMaze(string file_name)
{
	ifstream file(file_name.c_str());
	//file.open(file_name);
	string line;
	int cell_count = 0;

	if (file.is_open())
	{
		for (int row = 0; row < 5; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (getline(file, line))
				{
					stringstream ss(line);

					for (int height = 0; height < 5; ++height)
					{
						int value;
						if (ss >> value)
						{
							if (value == 0 || value == 1)
							{
								++cell_count;
								maze_temp[row][col][height] = value;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}

					}
				}

			}
			//empty line
			getline(file, line);
		}
		//check if there's more
		if (getline(file, line))
		{
			return false;
		}
	}

	file.close();
	if (cell_count != TOTAL_CELL || maze_temp[0][0][0] != 1 || maze_temp[4][4][4] != 1)
	{
		return false;
	}
	else
	{
		//maze_grid = maze_temp;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					maze_grid[i][j][k] = maze_temp[i][j][k];
				}
			}
		}

		return true;
	}

}

vector<string> Pathfinder::solveMaze()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			for (int k = 0; k < 5; ++k)
			{
				format_maze[i][j][k] = maze_grid[k][j][i];
			}
		}
	}

	solution.clear();
	if (find_maze_path(0, 0, 0))
	{	 
		return solution;
	}
	else
	{
		solution.clear();
		return solution;
	}
}

bool Pathfinder::find_maze_path(int x, int y, int z)
{
	
	solution.push_back("(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")");

	if (x < 0 || y < 0 || z < 0 || x > 4 || y > 4 || z > 4)
	{
		// out of bounds
		solution.pop_back();
		return false;
	}
	
	if (format_maze[x][y][z] != 1)
	{
		// not 1, or have been here before
		solution.pop_back();
		return false;
	}


	if (x == 4 && y == 4 && z == 4)
	{
		//found the path
		return true;
	}
	
	format_maze[x][y][z] = 2;

	if (find_maze_path(x+1, y, z))
	{
		return true;
	}
	if (find_maze_path(x-1, y, z))
	{
		return true;
	}
	if (find_maze_path(x, y, z-1))
	{
		return true;
	}
	if (find_maze_path(x, y, z+1))
	{
		return true;
	}
	if (find_maze_path(x, y+1, z))
	{
		return true;
	}
	if (find_maze_path(x, y-1, z))
	{
		return true;
	}

	solution.pop_back();
	return false;
	
}