#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include "heapV.h"

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


void msfPrim(Graph &g, Graph &sf);
// Finds minimum spanning forest of Graph g and stores it into Graph sf
void msfPrimHelper(Graph &g, Graph &sf, Graph::vertex_descriptor starting_node);
// Helper function for msfPrim. Called iteratively on every unmarked node (for disconnected graphs)

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
	cout << "Original Graph:" << endl << g << endl << endl;
	msfPrim(g, sf);
	cout << "Minimum Spanning Forest:" << endl << sf << endl;

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
		ostr << "Node:" << *vItr << " " << "Marked: " << g[*vItr].marked << " " << "Pred: " << g[*vItr].pred;
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


void msfPrim(Graph &g, Graph &sf)
{
	clearMarked(g);
	for (int i = 0; i < num_vertices(g); i++)
	{
		Graph::vertex_descriptor temp = add_vertex(sf);
	}

	pair < Graph::vertex_iterator, Graph::vertex_iterator > vItrRange1 = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange1.first; vItr != vItrRange1.second; vItr++)
	{
		if (g[*vItr].marked == false) // Calls msfPrimHelper on every unmarked node. In a connected graph, it is only called once
			msfPrimHelper(g, sf, *vItr);
	}
}

void msfPrimHelper(Graph &g, Graph &sf, Graph::vertex_descriptor starting_node)
{
	g[starting_node].marked = true;

	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); //All edges in graph


	bool edgeTest = false;
	for (int i = 0; i < num_vertices(g) - 1; i++)
	{
		vector<Graph::edge_descriptor> FringeEdges;
		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
		{
			Graph::vertex_descriptor Vertex1 = source(*eItr, g);
			Graph::vertex_descriptor Vertex2  = target(*eItr, g);
			if (g[Vertex1].marked == true && g[Vertex2].marked == false) // Stores all edges that depart from a marked node and lead to an unmarked node into FringeEdges vector
				FringeEdges.push_back(*eItr);
		}

		if (FringeEdges.size() > 0) //If a fringe edge exists
		{
			int smallest = INT_MAX;
			Graph::edge_descriptor MinEdge = FringeEdges[0];
			for (int j = 0; j < FringeEdges.size(); j++)
			{
				if (g[FringeEdges[j]].weight < smallest)
				{
					smallest = g[FringeEdges[j]].weight;
					MinEdge = FringeEdges[j]; //Extracts minimum edge from fringe
				}
			}

			Graph::vertex_descriptor V1 = source(MinEdge, g);
			Graph::vertex_descriptor V2 = target(MinEdge, g);
			add_edge(V1, V2, sf);
			add_edge(V2, V1, sf);
			pair<Graph::edge_descriptor, bool> edgePair1 = boost::edge(V1, V2, g); //Adds edge to spanning tree
			pair<Graph::edge_descriptor, bool> edgePair2 = boost::edge(V2, V1, g);

			pair<Graph::edge_descriptor, bool> edgeNewPair1 = boost::edge(V1, V2, sf);
			pair<Graph::edge_descriptor, bool> edgeNewPair2 = boost::edge(V2, V1, sf);

			sf[edgeNewPair1.first].weight = g[edgePair1.first].weight;
			sf[edgeNewPair2.first].weight = g[edgePair2.first].weight;

			g[V2].marked = true;
		}
		else // If no edge exists, the graph is disconnected and thus must terminate early to be called on another section of the graph (Graph is a forest instead of a tree)
		{
			i = INT_MAX - 1;
		}
	}
}