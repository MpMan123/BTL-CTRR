#ifndef TSM_H
#define TSM_H
#include <iostream>
#include "bellman.h"

extern int bestPath[100];
extern int currentPath[100]; 
extern bool visited[100];
extern int minWeight;
extern int bound;

// Sort the input graph in ascending order by graph[i][2]
void bsort(int** graph, int num_edges);
// Create a copy of input graph
int** CopyGraph(int graph[][3], int num_edges);
void destroy(int **graph, int num_edges);
// Traverse the graph using Depth-First Search
void dfs(vector<char>&list, int sumWeight, int numEdgePassed, int numVertices, int startIndex, vector<vector<int>>& matrix, int** graph, int num_edges);
// Calculate bound of each branch to obtain the mininum expected circuit weight
void calculateBound(vector<char>&list,int sumWeight, int numEdgePassed, int** graph, int num_edges, int numVertices);
// Print the tour that solves the Traveling Salesman Problem
string Traveling(int graph[][3], int num_edges, char start);

#endif