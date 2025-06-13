#ifndef TSM_H
#define TSM_H
#include <iostream>
#include "bellman.h"

extern int bestPath[100];
extern int bestPath[100];
extern int currentPath[100]; 
extern bool visited[100];

extern int minWeight;
extern int bound;

void bsort(int** graph, int num_edges);
// In ra đường ngắn nhất đi qua tất cả các đỉnh và quay trở lại đỉnh ban đầu
int** CopyGraph(int graph[][3], int num_edges);
void destroy(int **graph, int num_edges);
string Traveling(int graph[][3], int num_edges, char start);
void dfs(vector<char>&list, int sumWeight, int numEdgePassed, int numVertices, int startIndex, vector<vector<int>>& matrix, int** graph, int num_edges);
// Tạo ma trận liền kề
vector<vector<int>> getAdjacencyMatrix(int graph[][3], int num_edges);
void calculateBound(vector<char>&list,int sumWeight, int numEdgePassed, int** graph, int num_edges, int numVertices);
bool isValid(vector<char>& list,vector<vector<int>>& adjacencyMatrix, string& path, char vertex, int pos = 0);
void createPath(vector<string>& listOfPath, vector<char>&list, vector<vector<int>>& adjacencyMatrix);

#endif
/*
getAdjacency O(m*n)
m là số cạnh
n là số đỉnh
bsort O(m^2)
calculateBound O(m*n)
dfs O*/

/* Đã sửa bsort(int graph[][3], int num_edges) thành int** graph*/