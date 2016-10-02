#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include "maze.h"

using namespace boost;
using namespace std;

int recursecount = 0;
typedef boost::graph_traits < Graph >::adjacency_iterator adj;

#define FILENAME "maze0.txt" //Filename to load maze from

void clearVisited(Graph &g);
// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w);
// Set all node weights to w.

void clearMarked(Graph &g);
//Clears all nodes in g

ostream &operator<<(ostream &ostr, const Graph &g);
//Outputs all nodes and their propeties, and all edges and their properties in Graph g

void findPathDFSRecursive(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, bool &found);
// Finds a path to target from node using Depth-first search (Recursively)

void findPathDFSStack(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, bool &found);
// Finds a path to target from node using Depth-first search (via a Stack)

void findShortestPathDFS(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, stack<Graph::vertex_descriptor> &temp, int &length, bool &found);
// Finds the shortest path to target from node using Depth-first search (Recursively)

void findShortestPathBFS(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, bool &found);
// Finds a path to target from node using Breadth-first search (via a Queue)
   
int main()
{
   /*try
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
	  Graph::vertex_iterator vItrFirst = vItrRange.first;
	  Graph::vertex_iterator vItrSecond = vItrRange.second;
	  stack < Graph::vertex_descriptor > vStack0;
	  stack < Graph::vertex_descriptor > vStack1;
	  stack < Graph::vertex_descriptor > vStack2;
	  stack < Graph::vertex_descriptor > vStack3;
	  stack < Graph::vertex_descriptor > temp;
	  int length = INT_MAX;
	  bool found = false;

	  clearVisited(g);
	  
	  findPathDFSRecursive(g, (*vItrFirst), (*vItrSecond)-1, vStack0, found);
	  if (found == true)
		  m.printPath(*vItrSecond, vStack0, g);
	  else
		  cout << "No path exists" << endl;
	  found = false;
	  clearVisited(g);
	  

	  
	  findPathDFSStack(g, (*vItrFirst), *(vItrSecond)-1, vStack1, found);
	  if (found == true)
		  m.printPath(*vItrSecond, vStack1, g);
	  else
		  cout << "No path exists" << endl;
	  found = false;
	  clearVisited(g);
	  
	  findShortestPathDFS(g, (*vItrFirst), *(vItrSecond)-1, vStack2, temp, length, found);
	  if (found == true)
		  m.printPath(*vItrSecond, vStack2, g);
	  else
		  cout << "No path exists" << endl;
	  found = false;
	  clearVisited(g);

	  
	  findShortestPathBFS(g, (*vItrFirst), *(vItrSecond)-1, vStack3, found);
	  if (found == true)
		  m.printPath(*vItrSecond, vStack3, g);
	  else
		  cout << "No path exists" << endl;
	  clearVisited(g);

   }
   catch (std::invalid_argument &e)
   {
	   cout << "EXCEPTION THROWN: Invalid Argument\n";
   }*/


	int a = 10;
	while (a ++< 20)
	{
		cout << "ayylmao" << endl;
	}


	cout << endl;
	a = 10;


	while (a --\
				\
				 \
				  > 0) {
		cout << "ayylmao" << endl;
	}

	while (a --\
			  //\
		     //  \
	   _____//____\
	   \__________/
				 \
				  > 0) {
		cout << "ayylmao" << endl;
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


// Returns a stack of moves if a path is found
void findPathDFSRecursive(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, bool &found)
{
	g[node].visited = true;
	moves.push(node);
	pair<adj, adj> vItrRange = adjacent_vertices(node, g);


	for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		Graph::vertex_descriptor var = *vItr;
		if (*vItr == target) //If the target node is found
		{
			found = true; //set found bool equal to true
			moves.push(*vItr); //Push final node onto moves stack
		}
		else if (g[*vItr].visited == false && found == false) //For each unvisited neighbor assuming the target hasn't been found
		{
			Graph::vertex_descriptor cur = *vItr;
			findPathDFSRecursive(g, *vItr, target, moves, found); //Recurse on each neighbor
		}
	}
	if (found == false) //If target hasn't been found and all possible unvisited neighbors searched, pop node out
	moves.pop();
}


void findPathDFSStack(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &DFSstack, bool &found)
{
	if (DFSstack.size() > 0)
		throw std::invalid_argument("EXCEPTION_THROWN: Vars not empty");
	g[node].visited = true;
	DFSstack.push(node);

	while (!DFSstack.empty() && !found)
	{
		Graph::vertex_descriptor cur = DFSstack.top();
		bool hasNeighbors = false;

		pair<adj, adj> vItrRange = adjacent_vertices(cur, g);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) //For each unvisited neighbor assuming the target hasn't been found
		{
			Graph::vertex_descriptor var = *vItr;
			if (*vItr == target)
			{
				found = true; //Set found bool equal to true
				DFSstack.push(*vItr); //Push final node onto moves stack
				break;
			}
			else if (g[*vItr].visited == false && found == false)
			{
				Graph::vertex_descriptor cur = *vItr;
				g[cur].visited = true;
				DFSstack.push(cur); //Pushes unvisited neighbor onto the stack
				hasNeighbors = true; //
			}
		}
		if (!hasNeighbors && !found) //If no neighbors have been found, pops open the node
			DFSstack.pop();
	}
}

void findShortestPathDFS(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, stack<Graph::vertex_descriptor> &temp, int &length, bool &found)
{
	g[node].visited = true;
	temp.push(node);
	pair<adj, adj> vItrRange = adjacent_vertices(node, g);

	for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		Graph::vertex_descriptor var = *vItr;
		if (*vItr == target)
		{
			found = true;
			temp.push(*vItr);
			if (temp.size() < length) //If new path is shorter than old path
			{
				length = temp.size(); //Updates length to shorter path's length
				moves = temp; //Sets new path equal to old path
			}
		}
		else if (g[*vItr].visited == false) //Visits every unvisited neighbor
		{
			Graph::vertex_descriptor cur = *vItr;
			findShortestPathDFS(g, *vItr, target, moves, temp, length, found);
		}
	}
	g[node].visited = false; //Unvisits neighbors at the end
	temp.pop(); //Pops open temporary stack
}

void findShortestPathBFS(Graph &g, Graph::vertex_descriptor node, Graph::vertex_descriptor target, stack<Graph::vertex_descriptor> &moves, bool &found)
{
	if (moves.size() > 0)
		throw std::invalid_argument("EXCEPTION_THROWN: Vars not empty");
	
	queue<Graph::vertex_descriptor> temp; //Queue that stores neighbors

	temp.push(node); //Pushs and visits initial node onto the queue
	g[node].visited = true;
	moves.push(node);
	stack<Graph::vertex_descriptor> shortestPaths;
	int i = 0;


	i++;
	while (!temp.empty() && !found)
	{
		Graph::vertex_descriptor v = temp.front();

		pair<adj, adj> vItrRange = adjacent_vertices(v, g);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		{
			if (*vItr == target)
			{
				g[*vItr].pred = v; //Sets target's predecessor equal to parent node
				found = true;
				for (Graph::vertex_descriptor trace = *vItr; trace != node; trace = g[trace].pred) //Traces path backwards from target to source node
				{
					shortestPaths.push(trace);
				}
				shortestPaths.push(node);

				while (!shortestPaths.empty()) //Reverses stack and pushes it onto shortestPaths stack (which the final program uses)
				{
					moves.push(shortestPaths.top());
					shortestPaths.pop();
				}

			}
			else if (g[*vItr].visited == false && !found) //For every unvisited neighbor, push them onto the queue
			{	
				g[*vItr].visited = true;
				g[*vItr].pred = v; //Sets node's predecessor equal to parent node
				temp.push(*vItr);

				i++;
			}
		}
		temp.pop(); //Pop open first element in queue
	}

}