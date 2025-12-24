#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    // Constructor
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    // Add edge (undirected)
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    // Add edge (directed)
    void addDirectedEdge(int u, int v) {
        adjMatrix[u][v] = 1;
    }

    // Remove edge
    void removeEdge(int u, int v) {
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
    }

    // Print graph
    void printGraph() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }

    // BFS traversal
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int i = 0; i < V; i++) {
                if (adjMatrix[node][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    // DFS helper
    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int i = 0; i < V; i++) {
            if (adjMatrix[node][i] && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    // DFS traversal
    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Check if edge exists
    bool hasEdge(int u, int v) {
        return adjMatrix[u][v] == 1;
    }

    // Degree of vertex
    int degree(int v) {
        int deg = 0;
        for (int i = 0; i < V; i++)
            deg += adjMatrix[v][i];
        return deg;
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    g.printGraph();
    g.BFS(0);
    g.DFS(0);

    return 0;
}
