#include "tsm.h"
#define INF 1000000000

// Applying Held-Karp algorithm to find solution with more-than-25-vertex problem
string HKSolve(vector<vector<int>>& cost, int charToIndex[256], vector<char>& vertices, char start) {
    int numVertices = vertices.size();
    int states = 1 << numVertices;

    // Create spaces for "1 << numVertices" states
    vector<vector<int>> dp(states, vector<int>(numVertices, INF));
    vector<vector<int>> parent(states, vector<int>(numVertices, -1));

    int startIndex = charToIndex[start];
    
    dp[1 << startIndex][startIndex] = 0;

    for (int mask = 0; mask < states; ++mask) {
        for (int u = 0; u < numVertices; ++u) {
            // Inspect u's existence int state "mask"
            if (!(mask & (1 << u))) continue;

            if (dp[mask][u] >= INF) continue;
            for (int v = 0; v < numVertices; ++v) {
                if (mask & (1 << v)) continue;
                if (cost[u][v] == -1) continue; 

                int nextMask = mask | (1 << v);
                int dis = dp[mask][u] + cost[u][v];

                if (dis < dp[nextMask][v]) {
                    dp[nextMask][v] = dis;
                    parent[nextMask][v] = u;
                }
            }
        }
    }

    int minWeight = INF, last = -1;
    int finalMask = states - 1;

    for (int u = 0; u < numVertices; ++u) {
        if(u == startIndex || cost[u][startIndex] == -1) continue;
        int curWeight = dp[finalMask][u] + cost[u][startIndex];
        if (curWeight < minWeight) {
            minWeight = curWeight;
            last = u;
        }
    }

    if (minWeight >= INF) {
        return "";
    }

    vector<int> path;
    int mask = finalMask, u = last;
    while (u != -1) {
        path.push_back(u);
        int previous = parent[mask][u];
        mask ^= (1 << u);
        u = previous;
    }
    reverse(path.begin(), path.end());
    path.push_back(charToIndex[start]);
    
    string result = "";
    for (int i = 0; i < path.size(); ++i) {
        result += vertices[path[i]];
        if (i < path.size() - 1) {
            result += ' ';
        }
    }
    return result;
}

// Compute the total distance of the current tour
int calculatePath(vector<int>& currentPath, vector<vector<int>>& cost) {
    int numVertices = cost.size();
    int result = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (cost[currentPath[i]][currentPath[i + 1]] > 0) {
            result += cost[currentPath[i]][currentPath[i + 1]];
        }
        else return INF;
    }
    return result;
}

// Generate a neighboring solution by performing a 2-opt move
vector<int> getNeighbor(const vector<int>& currentPath, mt19937& rng) {
    vector<int> neighbor = currentPath;
    int numVertices = neighbor.size() - 1;

    // Swap 2 vertex randomly except the first and the last vertex
    uniform_int_distribution<int> dist(1, numVertices - 1);
    int i = dist(rng);
    int j = dist(rng);
    while (i == j) {
        j = dist(rng);
    }
    swap(neighbor[i], neighbor[j]);
    return neighbor;
}

// Applying Simulated Annealing algorithm
string SASolve(vector<vector<int>>& cost,int charToIndex[256], vector<char>& vertices, char start) {
    // Set up the first tour
    vector<int> currentPath;
    int startIndex = charToIndex[start];
    for (int i = 0; i < cost.size(); ++i) {
        if (i != startIndex) currentPath.push_back(i);
    }

    // Shuffled cities to form a randomized initial tour
    random_device rd;
    mt19937 rng(rd());
    shuffle(currentPath.begin(), currentPath.end(),rng);
    currentPath.insert(currentPath.begin(), startIndex);
    currentPath.push_back(startIndex);

    int bestCost = calculatePath(currentPath, cost);
    vector<int> bestPath = currentPath;

    // Initialize parameters
    double T = 1000;
    double T_min = 0.01;
    double alpha = 0.995;
    int iteration = 1000;

    uniform_real_distribution<double> prob(0.0, 1.0);

    while (T > T_min) {
        for (int i = 0; i < iteration; ++i) {
            vector<int> neighbor = getNeighbor(currentPath, rng);
            int currentCost = calculatePath(currentPath, cost);
            int neighborCost = calculatePath(neighbor, cost);
            int delta = neighborCost - currentCost;

            if (delta < 0 || prob(rng) < exp(-delta / T)) {
                currentPath = neighbor;
                if (neighborCost < bestCost) {
                    bestCost = neighborCost;
                    bestPath = neighbor;
                }
            }
        }
        T *= alpha;
    }

    string result = "";
    for (int i = 0; i < bestPath.size(); ++i) {
        result += vertices[bestPath[i]];
        if (i < bestPath.size() - 1) {
            result += ' ';
        }
    }

    if (bestCost < INF) return result;
    return "";
}

// Main solution using two algorithms above
string Traveling(int graph[][3], int num_edges, char start) {
    int numVertices = 0;
    vector<char> vertices;
    for (int i = 0; i < num_edges; ++i) {
        if (find(vertices.begin(), vertices.end(), static_cast<char>(graph[i][0])) == vertices.end()) {
            vertices.push_back(graph[i][0]);
            ++numVertices;
        }
        if (find(vertices.begin(), vertices.end(), static_cast<char>(graph[i][1])) == vertices.end()) {
            vertices.push_back(graph[i][1]);
            ++ numVertices;
        }
    }
    sort(vertices.begin(), vertices.end());
    int charToIndex[256];
    for (int i = 0; i < 256; ++i) {
        charToIndex[i] = -1;
    }
    for (int i = 0; i < numVertices; ++i) {
        charToIndex[vertices[i]] = i;
    }
    
    // Initialize a 2D matrix to perform distances between two different cities
    vector<vector<int>> cost(numVertices, vector<int>(numVertices, -1));
    for (int i = 0; i < num_edges; ++i) {
        int u = charToIndex[static_cast<char>(graph[i][0])];
        int v = charToIndex[static_cast<char>(graph[i][1])];
        if (cost[u][v] == -1 || cost[u][v] > graph[i][2])
            cost[u][v] = graph[i][2];
    }
    for (int i = 0; i < numVertices; ++i) {
        cost[i][i] = 0;
    }

    if (numVertices >= 25) {
        return SASolve(cost, charToIndex, vertices, start);
    }
    return HKSolve(cost, charToIndex, vertices, start);
}
    