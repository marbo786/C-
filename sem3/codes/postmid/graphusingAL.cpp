#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;                              // Number of vertices
    vector<vector<int>> adj;            // Adjacency list

public:
    // Constructor
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge (undirected)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Add edge (directed)
    void addDirectedEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Remove edge (undirected)
    void removeEdge(int u, int v) {
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
    }

    // Print graph
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int v : adj[i])
                cout << v << " ";
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

            for (int neigh : adj[node]) {
                if (!visited[neigh]) {
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }
        cout << endl;
    }

    // DFS helper
    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neigh : adj[node]) {
            if (!visited[neigh]) {
                DFSUtil(neigh, visited);
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
        return find(adj[u].begin(), adj[u].end(), v) != adj[u].end();
    }

    // Degree of vertex
    int degree(int v) {
        return adj[v].size();
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
