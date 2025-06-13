#include "tsm.h"

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

vector<vector<int>> getAdjacencyMatrix(int graph[][3], int num_edges) {
    int num_of_vertices = countVertices(graph, num_edges);
    vector<vector<int>> matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
    
    // Danh sach cac dinh
    vector<char> list_of_vertices = getVectorOfVertices(graph, num_edges);
    // Ma tran lien ke
    for (int i = 0; i < num_edges; ++i) {
        int u = findIndexInVector(list_of_vertices, graph[i][0]);
        int v = findIndexInVector(list_of_vertices, graph[i][1]);
        if (u >= 0 && v >= 0) {
            // Đam bao neu la đa đo thi, thi chi lay canh co trong so nho nhat
            if (matrix[u][v] == 0 || matrix[u][v] > graph[i][2])
                matrix[u][v] = graph[i][2];
        }
    }
    return matrix;
}

bool isValid(vector<char>& list, vector<vector<int>>& adjacencyMatrix,string& path, char vertex, int pos) {
    int size = path.size();

    // Neu ko ton tai duong di tu dinh cuoi cua path den dinh vertex

    if (!adjacencyMatrix[findIndexInVector(list, path[size - 1])][findIndexInVector(list,vertex)]) {
        return false;
    }

    // Neu chua du do dai
    if (pos < list.size()) {
        for (int i = 0; i < size; ++i) {
            if (path[i] == vertex) {
                return false;
            }
        }
        if (adjacencyMatrix[findIndexInVector(list, path[size - 1])][findIndexInVector(list,vertex)]) {
            return true;
        }
    }

    // neu da du do dai
    if (vertex != path[0]) {
        return false;
    }
    return true;
}

void createPath(vector<string>& listOfPath, vector<char>&list, vector<vector<int>>& adjacencyMatrix) {
    int numOfVertices = list.size();

    // Duyet tung chuoi con trong listOfPath
    for (int i = 0; i < listOfPath.size(); ++i) {
        string tmp = listOfPath[i];
        // Tao chuoi con theo tung bac, lenh for de duyet tat ca duong di co the o bac thu tmp.size()
        if (tmp.size() < numOfVertices + 1) {
            for (int j = 0; j < numOfVertices; ++j) {
                // Nếu tồn tại đường đi từ đỉnh cuối trên đg tmp tới đỉnh j
                if (adjacencyMatrix[findIndexInVector(list, tmp[tmp.size() - 1])][j]) {
                    // Kiem tra dinh j co hop le hay khong cho vi tri cuoi cua tmp
                    if (isValid(list,adjacencyMatrix, tmp, list[j], tmp.size())) {
                        listOfPath.push_back(tmp + list[j]);
                    }
                        
                }
            }
        }
    }
}

int bestPath[100];
int currentPath[100]; 
bool visited[100];

int minWeight = INT_MAX;
int bound = 0;


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
void calculateBound(vector<char>&list,int sumWeight, int numEdgePassed, int** graph, int num_edges, int numVertices) {
    bool tmp[100];
    for (int i = 0; i < numVertices; ++i) {
        tmp[i] = visited[i];
    }
    for (int i = 0; i < num_edges; ++i) {
        int v = findIndexInVector(list, graph[i][1]);
        // Neu chua gap canh do thi tinh bound;
        if (!tmp[v]) {
            // cout << "sumWeight hien tai la: " << sumWeight << endl;
            tmp[v] = true;
            // cout << " lay tu canh " << (char)graph[i][0] << (char)graph[i][1] << endl;
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
    // Neu da di den canh thu n thi xet co noi vao dinh dau hay khong
    if (numEdgePassed == numVertices) {
        if (matrix[startIndex][currentPath[0]]) {
            sumWeight += matrix[startIndex][currentPath[0]];
        // Neu chu trinh nho hon thi cap nhat
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
    // Sap xep lai graph theo chieu tang dan cua trong so moi canh
    minWeight = INT_MAX;
    int** tmp_graph = CopyGraph(graph, num_edges);
    bsort(tmp_graph, num_edges);
    // cout << start << " _----\n";
    vector<char> listVertices = getVectorOfVertices(graph, num_edges);
    int numVertices = listVertices.size();
    vector<vector<int>> matrix = getAdjacencyMatrix(graph, num_edges);
    // Xet moi duong di bac 1 tu dinh start
    int startIndex = findIndexInVector(listVertices, start);
    currentPath[0] = startIndex;
    for (int i = 0; i < numVertices; ++i) {
        // Duyệt từng nhánh lớn
        // cout << "Xet nhanh: " << listVertices[i] << endl;
        visited[startIndex] = true;
        dfs(listVertices, matrix[startIndex][i], 1, numVertices, i ,matrix, tmp_graph, num_edges);
    }   
    // cout << minWeight << endl;
    string result = "";
    for (int i = 0; i <= numVertices; ++i) {
        result += listVertices[bestPath[i]];
        if (i < numVertices ) {
            result += ' ';
        }
    }
    // Chinh lai visited
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }
    destroy(tmp_graph, num_edges);
    if (minWeight < INT_MAX) return result;
    else return "";
}


/*
    bool visited[] có kích thước n đỉnh để xét đã đi qua chưa
    int bound: cận dưới để cắt nhánh
    int minPath để xét đường đi nhỏ nhất

    HÀM
        - Tính bound dựa trên các cạnh có thể đi qua bằng việc cộng 
            n - i cạnh với i là số cạnh đã dùng
        - sort Graph tăng dần theo trọng số cạnh
        - backtrack để xét từng cây con
        - tạo 

*/
