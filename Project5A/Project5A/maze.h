// Sample solution for project #5

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <boost/graph/adjacency_list.hpp>

#include "d_except.h"
#include "d_matrix.h"

#define LargeValue 99999999

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;


class maze
{
public:
   maze(ifstream &fin);
   void print(int,int,int,int);
   bool isLegal(int i, int j);
   void mapMazeToGraph(Graph &g);
   void printPath(Graph::vertex_descriptor end,
                        stack<Graph::vertex_descriptor> s,
                        Graph g);
   int numRows(){return rows;};
   int numCols(){return cols;};

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   
   matrix<bool> value;
};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;
   
   char x;
   
   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(Graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
	if (num_edges(g) != 0)
		throw std::invalid_argument("EXCEPTION OCURRED: Graph not empty");

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int above = i - 1;
			int left = j - 1;
			
			Graph::vertex_descriptor v0 = boost::add_vertex(g);
			pair<int, int> coordinates(i, j);
			g[v0].visited = false;
			g[v0].cell = coordinates;
			g[v0].marked = false;
			if (value[i][j] == true)
			{
				g[v0].weight = 0;
			}
			else
			{
				g[v0].weight = 1;
			}

			int index = i * 5 + j; //Index of current vertex placed
			int indextop = -1; //Index of vertex above current vertex
			int indexleft = -1; //Index of vertex to the left of the current vertex
			int indextopleft = -1; //Index of vertex to the topleft of the current vertex

			// These if statements essentially check for if there are valid nodes above, to the left, and topleft of the current node (Valid as in the nodes exist)
			if (above >= 0)
				indextop = above * 5 + j;
			if (left >= 0)
				indexleft = i * 5 + left;
			if (above >= 0 && left >= 0)
				indextopleft = above * 5 + left;

			// These if statements check if the nodes above, left, and topleft are empty spaces that the solver can step through (not X's). If they are, an edge is placed
			// between them
			if (indextop >= 0 && g[index].weight == 0 && g[indextop].weight == 0)
				add_edge(index, indextop, g);
			if (indexleft >= 0 && g[index].weight == 0 && g[indexleft].weight == 0)
				add_edge(index, indexleft, g);
			if (indextopleft >= 0 && g[index].weight == 0 && g[indextopleft].weight == 0)
				add_edge(index, indextopleft, g);
		}
	}
}

void maze::printPath(Graph::vertex_descriptor end,
	stack<Graph::vertex_descriptor> s,
	Graph g)
{
	while (!s.empty())
	{
		Graph::vertex_descriptor vItr = s.top();
		s.pop();
		pair<int, int> goal = g[end-1].cell;
		pair<int, int> curr = g[vItr].cell;
		print(goal.first, goal.second, curr.first, curr.second);
	}
}