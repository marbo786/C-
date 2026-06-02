#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class graph{
    private:
    int v;
    vector<vector<int>> adj;
    public:

    graph(int vertices){
        v = vertices;
        adj.resize(v);
    }


    void addedge(int u,int v){          // undirected
        adj[u].push_back(v);
        adj[v].push_back(u);

    }

    void removeedge(int u,int v){
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v) , adj[u].end());
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), u) , adj[v].end());
    }

    void bfs(int start){
        vector<bool> visited(v,false);
        queue <int> q;

        visited[start] = true;
        q.push(start);
        cout<<"BFS: "<< " ";

        while(!q.empty()){

            int node = q.front();
            q.pop();
            cout<< node <<" ";


            for(int neigh : adj[node]){

                if(!visited[neigh]){
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }
        cout<<endl;
    }


    
};