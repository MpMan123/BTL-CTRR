#ifndef TSM_H
#define TSM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

// Applying Held-Karp algorithm to find solution with more-than-25-vertex problem
string HKSolve(vector<vector<int>>& cost, int charToIndex[256], vector<char>& vertices, char start);

// Compute the total distance of the current tour
int calculatePath(vector<int>& currentPath, vector<vector<int>>& cost);
// Generate a neighboring solution by performing a 2-opt move
vector<int> getNeighbor(const vector<int>& currentPath, mt19937& rng);
// Applying Simulated Annealing algorithm
string SASolve(vector<vector<int>>& cost,int charToIndex[256], vector<char>& vertices, char start);

// Main solution using two algorithms above
string Traveling(int graph[][3], int num_edges, char start);

#endif