#ifndef BELLMAN_H
#define BELLMAN_H
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


// Get a list of vertices sorted in ascending ASCII order
vector<char> getListVertices(int graph[][3], int num_edges);

int* CopyArray(int a[], int num_of_vertices);

// Create an adjacency matrix from input graph
vector<vector<int>> getAdjacencyMatrix(int graph[][3], int num_edges);
// Adjust value_array and previous_array at one step
void BF(int graph[][3], int num_edges, char start, int value_array[], int previous_array[]);

// Return a string containing paths from start to goal with the best result
string BF_Path(int graph[][3], int num_edges, char start, char goal);

#endif