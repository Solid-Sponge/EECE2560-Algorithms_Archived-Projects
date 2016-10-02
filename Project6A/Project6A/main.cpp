#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>

#include <boost/graph/adjacency_list.hpp>

#define FILENAME "graph3.txt"

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
pair<int,int> cell; // maze cell (x,y) value
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

#define LargeValue 99999999

void clearVisited(Graph &g);
// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w);
// Set all node weights to w.

void clearMarked(Graph &g);
// Clears marked nodes

void clearPred(Graph &g);

ostream &operator<<(ostream &ostr, const Graph &g);
// Outputs graph object

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);
// Reads in graph from file and stores graph into Graph &g. Also stores start and end descriptors into &start and &end


int findSpanningForest(Graph &g, Graph &sf, int &totalComponents);
// Creates spanning forest from Graph g and places it into empty graph sf. totalComponents is set equal to the amount of components in the spanning tree.
// Returns total cost 

void findPathDFSRecursive(Graph &g, Graph::vertex_descriptor node);
// DFS recursive traversal that doesn't unvisit, used in function isConnected()

bool isConnected(Graph &g);
// Returns true if graph is connected, false otherwise

void findShortestPathDFS(Graph &g, Graph::vertex_descriptor node, bool &found);
// DFS traversal that unvisits, used in function isCyclic()

bool isCyclic(Graph &g);
// Returns true is graph is cyclic, false otherwise

int main()
{
	ifstream fin;
	fin.open(FILENAME);
	if (!fin)
	{
		cerr << "Cannot open " << FILENAME << endl;
		exit(1);
	}

	Graph g;
	Graph sf;
	Graph::vertex_descriptor start;
	Graph::vertex_descriptor end;
	bool found = false;

	initializeGraph(g, start, end, fin);
	bool Connected = isConnected(g);
	bool Cyclic = isCyclic(g);

	if (Connected)
		cout << "Connected graph" << endl;
	else
		cout << "Disconnected graph" << endl;

	if (Cyclic)
		cout << "Graph contains a cycle" << endl;
	else
		cout << "Graph doesn't contain a cycle" << endl;

	cout << "Original Graph" << endl << endl << g << endl;
	clearVisited(g);
	
	int totalComponents;
	int cost = findSpanningForest(g, sf,totalComponents);
	Connected = isConnected(sf);

	clearVisited(sf);
	Cyclic = isCyclic(sf);

	if (Connected)
		cout << "Connected graph (Spanning Tree)" << endl;
	else
		cout << "Disconnected graph (Spanning Tree)" << endl;

	if (Cyclic)
		cout << "Graph contains a cycle (Something went wrong with generating the Spanning Tree)" << endl;
	else
		cout << "Graph doesn't contain a cycle (Spanning Tree generated properly)" << endl;

	cout << "Spanning Tree" << endl  << endl << sf << endl;
	cout << endl << "Total Cost: " << cost << endl << "Total Components: " << totalComponents << endl;

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

void clearPred(Graph &g)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) //Iterates through every node and sets Marked to false on every node
	{
		g[*vItr].pred = -1;
	}
}

ostream &operator<<(ostream &ostr, const Graph &g)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange = vertices(g);

	cout << "Nodes: " << endl;
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		ostr << "(" << g[*vItr].cell.first << "," << g[*vItr].cell.second << ") " << "Marked: " << g[*vItr].marked << " " << "Pred: " << g[*vItr].pred;
		ostr << " " << "Visited: " << g[*vItr].visited << " " << "Weight: " << g[*vItr].weight << " " << endl;
	}

	pair < Graph::edge_iterator, Graph::edge_iterator > eItrRange = edges(g);


	cout << "Edges: " << endl;
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
	{
		ostr << *eItr << " " << "Weight: " << g[*eItr].weight << " " << "Visited: " << g[*eItr].visited << " " << "Marked: " << g[*eItr].marked << endl;
	}

	return ostr;
}


void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	//fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		/*if (i == startId)
			start = v;
		if (i == endId)
			end = v;*/
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}


int findSpanningForest(Graph &g, Graph &sf, int &totalComponents)
{
	totalComponents = 0;
	int size = num_vertices(g);
	while (size --\
			       \
			        \
		             \
				      >0) //This is a special easter egg in C++. Pay no attention to what it does, it just werks
	{
		Graph::vertex_descriptor temp = add_vertex(sf); //Essentially copies all nodes from graph G to target
	}
	
	int totalcost = 0;
	clearVisited(sf);
	
	queue<Graph::vertex_descriptor> temp; //Queue that stores neighbors
	EdgeProperties e;
	

	pair < Graph::vertex_iterator, Graph::vertex_iterator > All = vertices(sf);
	for (Graph::vertex_iterator vall = All.first; vall != All.second; vall++) //Iterates through every node
	{
		Graph::vertex_descriptor node = *vall;
		if (g[node].visited == false) //Checks each unvisited node (used to generate spanning forests when original graph is disconnected)
		{
			totalComponents++;

			temp.push(node); //Pushs and visits initial node onto the queue
			g[node].visited = true;

			while (!temp.empty())
			{
				Graph::vertex_descriptor v = temp.front();

				pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
				for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
				{
					Graph::vertex_descriptor debug = *vItr;
					if (g[*vItr].visited == false) //For every unvisited neighbor, push them onto the queue
					{
						g[*vItr].visited = true;
						g[*vItr].pred = v; //Sets node's predecessor equal to parent node
						add_edge(v, *vItr, e, sf);
						add_edge(*vItr, v, e, sf);

						pair<Graph::edge_descriptor, bool> edgePair1 = boost::edge(v, *vItr, g); //Adds edge to spanning tree
						pair<Graph::edge_descriptor, bool> edgePair2 = boost::edge(*vItr, v, g);
						pair<Graph::edge_descriptor, bool> edgeNewPair1 = boost::edge(v, *vItr, sf);
						pair<Graph::edge_descriptor, bool> edgeNewPair2 = boost::edge(*vItr, v, sf);

						totalcost += g[edgePair1.first].weight;

						sf[edgeNewPair1.first].weight = g[edgePair1.first].weight;
						sf[edgeNewPair2.first].weight = g[edgePair2.first].weight;

						temp.push(*vItr);
					}
				}
				temp.pop(); //Pop open first element in queue
			}
		}
	}
	clearVisited(sf);

	return totalcost;
}


void findPathDFSRecursive(Graph &g, Graph::vertex_descriptor node)
{
	g[node].visited = true;
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(node, g);


	for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		Graph::vertex_descriptor var = *vItr;
		if (g[*vItr].visited == false) //For each unvisited neighbor assuming the target hasn't been found
		{
			Graph::vertex_descriptor cur = *vItr;
			findPathDFSRecursive(g, *vItr); //Recurse on each neighbor
		}
	}
}

//Returns true if graph is connected
bool isConnected(Graph &g)
{
	clearMarked(g);
	clearVisited(g);

	findPathDFSRecursive(g, 0);
	

	pair < Graph::vertex_iterator, Graph::vertex_iterator > All = vertices(g);
	for (Graph::vertex_iterator v = All.first; v != All.second; v++) //Iterates through every node and sets Marked to false on every node
	{
		if (g[*v].visited == false)
			return false;
	}

	return true;
}

void findShortestPathDFS(Graph &g, Graph::vertex_descriptor node, bool &found)
{
	g[node].visited = true;
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(node, g);

	for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		Graph::vertex_descriptor var = *vItr;
		
		//if (g[*vItr].pred != node && g[*vItr].visited == true)
		if (g[node].pred != *vItr && g[*vItr].visited == true)
		{
			found = true;
		}

		else if (g[*vItr].visited == false) //Visits every unvisited neighbor
		{
			Graph::vertex_descriptor cur = *vItr;
			g[cur].pred = node;
			findShortestPathDFS(g, *vItr, found);
		}
	}
	g[node].visited = false; //Unvisits neighbors at the end
}

//Returns true is graph is Cyclic
bool isCyclic(Graph &g)
{
	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange1 = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange1.first; vItr != vItrRange1.second; vItr++)
	{
		bool found = false;
		findShortestPathDFS(g, *vItr, found);
		if (found)
			return true;
		clearPred(g);
		clearVisited(g);
	}
	return false;
}