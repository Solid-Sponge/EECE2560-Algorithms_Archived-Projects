#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include "maze.h"

using namespace boost;
using namespace std;


#define FILENAME "maze0.txt" //Filename to maze from

void clearVisited(Graph &g);
// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w);
// Set all node weights to w.

void clearMarked(Graph &g);
//Clears all nodes in g

ostream &operator<<(ostream &ostr, const Graph &g);
//Outputs all nodes and their propeties, and all edges and their properties in Graph g
   
int main()
{
   try
   {
      ifstream fin;

      
      //fin.open(fileName.c_str());
	  fin.open(FILENAME);
      if (!fin)
      {
         cerr << "Cannot open " << FILENAME << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();
      
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      Graph g;
      m.mapMazeToGraph(g);
	  

	  //Creates a stack of vertex_descriptors to test the printPath function
	  pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	  Graph::vertex_iterator vItr = vItrRange.second;
	  stack < Graph::vertex_descriptor > vStack;
	  vStack.push(*(vItrRange.first+1));

	  m.printPath(*vItr,vStack, g);

	  clearVisited(g);

      cout << g << endl;
   }
   catch (std::invalid_argument &e)
   {

   }
}

void clearVisited(Graph &g)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) //Iterates through every node and sets visited to false on every node
	{
		g[*vItr].visited = false;
	}
}

void setNodeWeights(Graph &g, int w)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) //Iterates through every node and sets the nodeWeight equal to w on every node
	{
		g[*vItr].weight = w;
	}
}

void clearMarked(Graph &g)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) //Iterates through every node and sets Marked to false on every node
	{
		g[*vItr].marked = false;
	}
}

ostream &operator<<(ostream &ostr, const Graph &g)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		ostr << "(" << g[*vItr].cell.first << "," << g[*vItr].cell.second << ") " << g[*vItr].marked << " " << g[*vItr].pred << " " << g[*vItr].visited << " " << g[*vItr].weight << " " << endl;
	}

	pair < Graph::edge_iterator, Graph::edge_iterator > eItrRange = edges(g);



	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
	{
		ostr << *eItr << " " << g[*eItr].weight << " " << g[*eItr].visited << " " << g[*eItr].marked << endl;
	}

	return ostr;
}