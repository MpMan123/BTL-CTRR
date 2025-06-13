#include "tsm.h"

int bestPath[100];
int currentPath[100]; 
bool visited[100];
int minWeight = INT_MAX;
int bound = 0;

void bsort(int** graph, int num_edges) {
    for (int i = 0; i < num_edges; ++i) {
        for (int j = 0; j < num_edges - i - 1; ++j) {
            if (graph[j][2] > graph[j + 1][2]) {
                // Swap từng phần tử
                for (int k = 0; k < 3; ++k) {
                    int tmp = graph[j][k];
                    graph[j][k] = graph[j + 1][k];
                    graph[j + 1][k] = tmp;
                }
            }
        }
    }
}

int** CopyGraph(int graph[][3], int num_edges) {
    int** newGraph = new int*[num_edges];
    for (int i = 0; i < num_edges; ++i) {
        newGraph[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            newGraph[i][j] = graph[i][j];
        }
    }
    return newGraph;
}
void destroy(int** graph, int num_edges) {
    for (int i = 0; i < num_edges; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
}

vector<vector<int>> getAdjacencyMatrix(int graph[][3], int num_edges) {
    int num_of_vertices = countVertices(graph, num_edges);
    vector<vector<int>> matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
    
    vector<char> list_of_vertices = getVectorOfVertices(graph, num_edges);

    for (int i = 0; i < num_edges; ++i) {
        int u = findIndexInVector(list_of_vertices, graph[i][0]);
        int v = findIndexInVector(list_of_vertices, graph[i][1]);
        if (u >= 0 && v >= 0) {
            // Ensure that if the graph is a multigraph, only the edge with the smallest weight is kept
            if (matrix[u][v] == 0 || matrix[u][v] > graph[i][2])
                matrix[u][v] = graph[i][2];
        }
    }
    return matrix;
}

void calculateBound(vector<char>&list,int sumWeight, int numEdgePassed, int** graph, int num_edges, int numVertices) {
    bool tmp[100];
    for (int i = 0; i < numVertices; ++i) {
        tmp[i] = visited[i];
    }
    for (int i = 0; i < num_edges; ++i) {
        int v = findIndexInVector(list, graph[i][1]);
        // Estimate the lower bound using the remaining unvisited edges
        if (!tmp[v]) {
            tmp[v] = true;
            sumWeight += graph[i][2];
            ++numEdgePassed; 
        }
        if (numEdgePassed == numVertices) {
            bound = sumWeight;
            return;
        }
    }
}

void dfs(vector<char>& list, int sumWeight, int numEdgePassed, int numVertices, int startIndex, vector<vector<int>>& matrix, int** graph, int num_edges) {
    // Verify the existence of a circuit
    if (numEdgePassed == numVertices) {
        if (matrix[startIndex][currentPath[0]]) {
            sumWeight += matrix[startIndex][currentPath[0]];
            // Update minWeight when a better result is found
            if (sumWeight < minWeight) {
                minWeight = sumWeight;
                for (int i = 0; i < numVertices; ++i) {
                    bestPath[i] = currentPath[i];
                }
            }
        }
        return;
    }

    for (int v = 0; v < numVertices; ++v) {
        if (matrix[startIndex][v]) {
            if (!visited[v]) {
                calculateBound(list, sumWeight, numEdgePassed, graph, num_edges, numVertices);
                visited[v] = true;
                if (bound < minWeight) {
                    currentPath[numEdgePassed] = v;
                    dfs(list, sumWeight + matrix[startIndex][v], numEdgePassed + 1, numVertices, v, matrix, graph, num_edges);
                }
                visited[v] = false;
            }
        }
    }
}

string Traveling(int graph[][3], int num_edges, char start) { 
    minWeight = INT_MAX;
    int** tmp_graph = CopyGraph(graph, num_edges);
    bsort(tmp_graph, num_edges);

    vector<char> listVertices = getVectorOfVertices(graph, num_edges);
    int numVertices = listVertices.size();
    vector<vector<int>> matrix = getAdjacencyMatrix(graph, num_edges);

    int startIndex = findIndexInVector(listVertices, start);
    currentPath[0] = startIndex;
    for (int i = 0; i < numVertices; ++i) {
        // Traverse each major branch
        visited[startIndex] = true;
        dfs(listVertices, matrix[startIndex][i], 1, numVertices, i ,matrix, tmp_graph, num_edges);
    }   

    string result = "";
    for (int i = 0; i <= numVertices; ++i) {
        result += listVertices[bestPath[i]];
        if (i < numVertices ) {
            result += ' ';
        }
    }
    // Reset the value of visited array
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }
    // Free the memory allocated for tmp_graph
    destroy(tmp_graph, num_edges);
    if (minWeight < INT_MAX) return result;
    else return "";
}
