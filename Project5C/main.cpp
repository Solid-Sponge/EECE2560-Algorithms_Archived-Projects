#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include "heapV.h"

#define FILENAME "graph1.txt"

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

ostream &operator<<(ostream &ostr, const Graph &g);
// Outputs graph object

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);
// Reads in graph from file and stores graph into Graph &g. Also stores start and end descriptors into &start and &end

void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
// Relaxes edge between vertex u and v

bool dijkstra(Graph &g, Graph::vertex_descriptor s);
// Performs Dijkstra's Algorithm on Graph g with starting node s. Returns false if no path to every node exists, true otherwise

bool bellmanFord(Graph &g, Graph::vertex_descriptor s);
// Performs Bellman-Ford's Algorithm on Graph g with starting node s. Returns false if no path to every node exists OR negative cycle detected
// True otherwise

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
	Graph::vertex_descriptor start;
	Graph::vertex_descriptor end;

	initializeGraph(g, start, end, fin);

	bool Dijkstras = dijkstra(g, start);
	bool Bellman = bellmanFord(g, start);
	if (Dijkstras)
		cout << "Shortest path to every node found with Dijsktra's Algorithm" << endl;
	else
		cout << "Unreachable node detected in graph" << endl;
	if (Bellman)
		cout << "Shortest path to every node found with Bellman-Ford's Algorithm" << endl;
	else
		cout << "Unreachable node or negative cycle detected in graph" << endl;
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

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}

void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	pair<Graph::edge_descriptor, bool> edgePair = boost::edge(u, v, g);
	Graph::edge_descriptor edge = edgePair.first;

	if (g[v].weight > g[u].weight + g[edge].weight)
	{
		g[v].weight = g[u].weight + g[edge].weight;
		g[v].pred = u;
	}
}

bool dijkstra(Graph &g, Graph::vertex_descriptor s)
{
	setNodeWeights(g, LargeValue);
	g[s].weight = 0;

	heapV<Graph::vertex_descriptor, Graph> priority_queue;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) // Push all nodes into priority-queue
		priority_queue.minHeapInsert(*vItr, g);

	while (priority_queue.size() > 0)
	{
		Graph::vertex_descriptor u = priority_queue.extractMinHeapMinimum(g);

		pair < Graph::adjacency_iterator, Graph::adjacency_iterator> neighborRange = adjacent_vertices(u, g);
		for (Graph::adjacency_iterator vI = neighborRange.first; vI != neighborRange.second; vI++)
		{
			Graph::vertex_descriptor v = *vI;
			relax(g, u, v);
		}
		priority_queue.buildMinHeap(priority_queue.size(), g);
	}

	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if (g[*vItr].weight == LargeValue)
			return false;
	}
	return true;
}

bool bellmanFord(Graph &g, Graph::vertex_descriptor s)
{
	setNodeWeights(g, LargeValue);
	g[s].weight = 0;
	
	for (int i = 0; i < num_vertices(g); i++)
	{
		//for each edge(u,v) -> relax(u,v)
		pair < Graph::edge_iterator, Graph::edge_iterator> edgeItrRange = edges(g);
		for (Graph::edge_iterator edgeItr = edgeItrRange.first; edgeItr != edgeItrRange.second; edgeItr++)
		{
			Graph::vertex_descriptor u = source(*edgeItr, g);
			Graph::vertex_descriptor v = target(*edgeItr, g);
			relax(g, u, v);
		}
	}
	// Check for negative cycles
	pair < Graph::edge_iterator, Graph::edge_iterator> edgeItrRange = edges(g);
	for (Graph::edge_iterator edgeItr = edgeItrRange.first; edgeItr != edgeItrRange.second; edgeItr++)
	{
		Graph::vertex_descriptor u = source(*edgeItr, g);
		Graph::vertex_descriptor v = target(*edgeItr, g);
		if (g[v].weight > g[u].weight + g[*edgeItr].weight)
		{
			//cout << "Negative Cycle Detected" << endl;
			return false;
		}
	}

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if (g[*vItr].weight == LargeValue)
			return false;
	}

	return true;
}