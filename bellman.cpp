#include "bellman.h"

void sort(vector<char>& vectorOfVertices) {
    int size = vectorOfVertices.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (vectorOfVertices[j] > vectorOfVertices[j + 1]) {
                char tmp = vectorOfVertices[j];
                vectorOfVertices[j] = vectorOfVertices[j + 1];
                vectorOfVertices[j + 1] = tmp;
            }
        }
    }
}

int countVertices(int graph[][3], int num_edges) {
    int exist[256] = {0};
    for (int i = 0; i < num_edges; ++i) {
        if (exist[graph[i][0]] == 0) {
            ++exist[graph[i][0]];
        }
        if (exist[graph[i][1]] == 0) {
            ++exist[graph[i][1]];
        }
    }
    int sum = 0;
    for (int i = 0; i < 256; ++i) {
        sum += exist[i];
    }
    return sum;
}

int findIndexInVector(vector<char> list, char vertex) {
    int size = list.size();
    for (int i = 0; i < size; ++i) {
        if (vertex == list[i]) {
            return i;
        }
    }
    return -1;
}

int* CopyArray(int a[], int num_of_vertices) {
    int* result = new int[num_of_vertices];
    for (int i = 0; i < num_of_vertices; ++i) {
        result[i] = a[i];
    }
    return result;
}

void BF(int graph[][3], int num_edges, char start, int value_array[], int previous_array[]) {
    int num_of_vertices = countVertices(graph, num_edges);
    vector<char> list_of_vertices = getVectorOfVertices(graph, num_edges);
    
    int start_index = findIndexInVector(list_of_vertices, start);

    // Initialize the weight of the starting node to 0
    value_array[start_index] = 0; 
    int u, v;

    // Get the copy of valueArray and previousArray of the step before
    int* tmp_value = CopyArray(value_array,num_of_vertices);
    int* tmp_pre = CopyArray(previous_array, num_of_vertices);

    for (int i = 0; i < num_edges; ++i) {
        u = findIndexInVector(list_of_vertices, (char)graph[i][0]);
        v = findIndexInVector(list_of_vertices, (char)graph[i][1]);
        if (tmp_value[u] != -1) {
            if((value_array[u] + graph[i][2] < value_array[v]) || value_array[v] == -1) {
                value_array[v] = value_array[u] + graph[i][2];
                previous_array[v] = graph[i][0];
            }
        }
    }
    delete[] tmp_value;
    delete[] tmp_pre;
}

vector<char> getVectorOfVertices(int graph[][3], int num_edges) {
    int num_of_vertices = countVertices(graph, num_edges);
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
    sort(list);
    return list;
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
    
    int num_of_vertices = countVertices(graph, num_edges);
    int* value_array = new int[num_of_vertices];
    int* previous_array = new int[num_of_vertices];

    for (int i = 0; i < num_of_vertices; ++i) {
        value_array[i] = -1;
        previous_array[i] = -1;
    }

    for (int i = 0; i < num_of_vertices; ++i) {
        BF(graph, num_edges, start, value_array, previous_array);
    }


    vector<char> list = getVectorOfVertices(graph, num_edges);
    string result = "";
    char tmp = goal;
    while (tmp != -1) {
        result = result + tmp;
        tmp = previous_array[findIndexInVector(list, tmp)];
        if ((int)tmp != -1) {
            result += ' ';
        }
    }
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





