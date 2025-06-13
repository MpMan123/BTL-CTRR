#ifndef BELLMAN_H
#define BELLMAN_H
#include <iostream>
#include <vector>
using namespace std;

void sort(vector<char>& vectorOfVertices);
// Chỉ thay đổi mảng value_array và previous_array
// graph bao gồm đỉnh đầu, đỉnh cuối và trọng số đường đi
void BF(int graph[][3], int num_edges, char start, int value_array[], int previous_array[]);
// Trả về chuỗi chứa con đường ngắn nhất từ đỉnh start đến goal
string BF_Path(int graph[][3], int num_edges, char start, char goal);
// Trả về "A D C B" -> đi qua A -> D -> C -> B
int countVertices(int graph[][3], int num_edges);
int* CopyArray(int a[], int num_of_vertices);
// Tìm xem chỉ số của đỉnh là bao nhiêu
// int findIndex(char list[], char vertex, int num_of_vertices);
int findIndexInVector(vector<char> list, char vertex);
// char* getListVertices(int graph[][3], int num_edges);
vector<char> getVectorOfVertices(int graph[][3], int num_edges);
int shortestValue(int graph[][3], int num_edges, vector<char>& list, char start, char goal);
#endif