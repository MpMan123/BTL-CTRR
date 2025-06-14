#ifndef BELLMAN_H
#define BELLMAN_H
#include <iostream>
#include <vector>
using namespace std;

// Sort the list of vertices in asceding ASCII order
void sort(vector<char>& vectorOfVertices);
// Count the number of vertices in the graph
int countVertices(int graph[][3], int num_edges);

// Get a list of vertices sorted in ascending ASCII order
vector<char> getVectorOfVertices(int graph[][3], int num_edges);

int findIndexInVector(vector<char> list, char vertex);
int* CopyArray(int a[], int num_of_vertices);

// Create an adjacency matrix from input graph
vector<vector<int>> getAdjacencyMatrix(int graph[][3], int num_edges);
// Adjust value_array and previous_array at one step
void BF(int graph[][3], int num_edges, char start, int value_array[], int previous_array[]);

// Return a string containing paths from start to goal with the best result
string BF_Path(int graph[][3], int num_edges, char start, char goal);

#endif