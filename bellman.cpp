#include "bellman.h"

vector<char> getListVertices(int graph[][3], int num_edges) {
    vector<char> list;

    int index = 0;
    int exist[256] = {0};
    for (int i = 0; i < num_edges; ++i) {
        if (exist[graph[i][0]] == 0) {
            ++exist[graph[i][0]];
            list.push_back((char)graph[i][0]);
        }
        if (exist[graph[i][1]] == 0) {
            ++exist[graph[i][1]];
            list.push_back((char)graph[i][1]);
        }
    }
    sort(list.begin(), list.end());
    return list;
}


int* CopyArray(int a[], int num_of_vertices) {
    int* result = new int[num_of_vertices];
    for (int i = 0; i < num_of_vertices; ++i) {
        result[i] = a[i];
    }
    return result;
}

vector<vector<int>> getAdjacencyMatrix(int graph[][3], int num_edges) {
    vector<char> list_of_vertices = getListVertices(graph, num_edges);
    int num_of_vertices = list_of_vertices.size();
    vector<vector<int>> matrix(num_of_vertices, vector<int>(num_of_vertices, -1));

    int charToIndex[256];
    for (int i = 0; i < 256; ++i) {
        charToIndex[i] = -1;
    }
    for (int i = 0; i < num_of_vertices; ++i) {
        charToIndex[list_of_vertices[i]] = i;
    }

    for (int i = 0; i < num_edges; ++i) {
        int u = charToIndex[graph[i][0]];
        int v = charToIndex[graph[i][1]];
        if (u >= 0 && v >= 0) {
            // Ensure that if the graph is a multigraph, only the edge with the smallest weight is kept
            if (matrix[u][v] == -1 || matrix[u][v] > graph[i][2])
                matrix[u][v] = graph[i][2];
        }
    }
    for (int i = 0; i < num_of_vertices; ++i) {
        matrix[i][i] = 0;
    }
    return matrix;
}

void BF(int graph[][3], int num_edges, char start, int value_array[], int previous_array[]) {
    vector<char> list_of_vertices = getListVertices(graph, num_edges);
    int num_of_vertices = list_of_vertices.size();
    vector<vector<int>> adjacencyMatrix = getAdjacencyMatrix(graph,num_edges);

    int charToIndex[256];
    for (int i = 0; i < 256; ++i) {
        charToIndex[i] = -1;
    }
    for (int i = 0; i < num_of_vertices; ++i) {
        charToIndex[list_of_vertices[i]] = i;
    }

    int start_index = charToIndex[start];
    // Initialize the weight of the starting node to 0
    value_array[start_index] = 0; 

    // Get the copy of valueArray and previousArray of the step before
    int* tmp_value = CopyArray(value_array,num_of_vertices);

    
    for (int i = 0; i < num_of_vertices; ++i) {
        
        if (tmp_value[i] == -1) continue;
        for (int j = 0; j < num_of_vertices; ++j) {
            if (adjacencyMatrix[i][j] <= 0) continue;

            int dis = tmp_value[i] + adjacencyMatrix[i][j];

            if (dis < value_array[j] || value_array[j] == -1) {
                value_array[j] = dis;
                previous_array[j] = i;
            }
        }
    }
    delete[] tmp_value;
}

string BF_Path(int graph[][3], int num_edges, char start, char goal) {
    bool in = false;
    bool out = false;
    
    // Check the existence of path from any vertices to goal and path from start to any other vertices
    for (int i = 0; i < num_edges; ++i) {
        if (start == (char)graph[i][0]) {
            out = true;
        }
        if (goal == (char)graph[i][1]) {
            in = true;
        }
    }
    if (in == false || out == false) {
        return "";
    }
    
    vector<char> list_of_vertices = getListVertices(graph, num_edges);
    int num_of_vertices = list_of_vertices.size();
    int* value_array = new int[num_of_vertices];
    int* previous_array = new int[num_of_vertices];

    int charToIndex[256];
    for (int i = 0; i < 256; ++i) {
        charToIndex[i] = -1;
    }
    for (int i = 0; i < num_of_vertices; ++i) {
        charToIndex[list_of_vertices[i]] = i;
    }

    for (int i = 0; i < num_of_vertices; ++i) {
        value_array[i] = -1;
        previous_array[i] = -1;
    }

    for (int i = 0; i < num_of_vertices; ++i) {
        BF(graph, num_edges, start, value_array, previous_array);
    }


    vector<char> list = getListVertices(graph, num_edges);
    string result = "";
    char tmp = goal;
    int pre_vertice_index;
    do {
        result = result + tmp;
        pre_vertice_index = previous_array[charToIndex[tmp]];
        if (pre_vertice_index != -1) {
            tmp = list[pre_vertice_index];
            result += ' ';
        }
        
    } while (pre_vertice_index != -1);
    int size = result.size();
    for (int i = 0; i < size / 2; ++i) {
        char k = result[i];
        result[i] = result[size - i - 1];
        result[size - i - 1] = k;
    }
    delete[] value_array;
    delete[] previous_array;
    return result;
}





