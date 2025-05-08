// parallel_dfs_userinput.cpp
#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(startVertex);

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";

                #pragma omp parallel for
                for (int i = 0; i < adj[v].size(); ++i) {
                    int n = adj[v][i];
                    if (!visited[n]) {
                        #pragma omp critical
                        s.push(n);
                    }
                }
            }
        }
    }
};

int main() {
    int V, E, start;
    cout << "Enter number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter edges (from to):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
        g.addEdge(v, u);  // Undirected graph
    }

    cout << "Enter starting vertex for DFS: ";
    cin >> start;

    cout << "Parallel DFS traversal: ";
    g.parallelDFS(start);
    cout << endl;
    return 0;
}
