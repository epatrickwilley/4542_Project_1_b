// Code to read graph instances from a file.  Uses the Boost Graph Library (BGL).
//This is the graph matching main file

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <fstream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

int initializeGraph(Graph &g, ifstream &fin)
// Initialize g using data from fin.  
{
	int numcolors;
	int n, e;
	int j, k;
	fin >> numcolors;
	fin >> n >> e;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
		v = add_vertex(g);

	for (int i = 0; i < e; i++)
	{
		fin >> j >> k;
		add_edge(j, k, g);  // Assumes vertex list is type vecS
	}

	return numcolors;
}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].weight = w;
	}
}

int main()
{
	char x;
	ifstream fin;
	string fileName;
	int stopper;
	vector<int> colors;
	int trials = 0;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.


	fileName = "color12-3.input";

	cin >> stopper;

	//   cout << "Enter filename" << endl;
	//   cin >> fileName;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading graph" << endl;
		Graph g;
		int numcolors = initializeGraph(g, fin);
		colors.resize(num_vertices(g), 0);
		trials = pow(numcolors, num_vertices(g)); // ex. 3 digit comb lock = 10^3

		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		cin >> stopper;

		for (int i = 0; i < trials; i++) //runs for number of combinations
		{
			cout << "Trial:" << i << endl;
			//check for conflicts

			int j = num_vertices(g) - 1;
			int basenum = i;

			while (basenum != 0 && j > -1) // creates a base number for the colors 
			{
				colors[j] = basenum % numcolors;
				basenum = basenum / numcolors;
				j--;
			}

			for (int k = 0; k < num_vertices(g); k++)
			{
				cout << colors[k];
			}
			cout<<endl;

		}
	}
	catch(int y)
	{
		cout << "An exception occured" <<endl;
	}


}