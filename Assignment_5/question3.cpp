#include <iostream>
#include <vector>
using namespace std;

bool validateSpanningTree(vector<vector<double>>& adj, vector<vector<double>>& edges, int n) {
    int m = edges.size();
    if (m != n - 1) {
        return false;
    }

    vector<bool> visited(n, 0);

    for (auto edge: edges) {
        double u = edge[0];
        double v = edge[1];
        double wt = edge[2];
        if (adj[u][v] != wt) {
            return false;
        }
        visited[u] = visited[v] = 1;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m, mSpan;
    cout << "Enter the number of vertices : ";
    cin >> n;
    cout << "Enter the number of edges in the graph : ";
    cin >> m;
    
    vector<vector<double>> edges;
    vector<vector<double>> adj(n, vector<double>(n, 0));

    cout << "Enter the graph edges . . . \n";
    for (int i = 0; i < m; ++i) {
        double u, v, wt;
        cin >> u >> v >> wt;
        adj[u][v] = adj[v][u] = wt;
    }

    cout << "Enter the number of edges : ";
    cin >> mSpan;
    for (int i = 0; i < mSpan; ++i) {
        double u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }

    bool result = validateSpanningTree(adj, edges, n);
    if (result) {
        cout << "The given graph is a valid spanning tree.\n";
    }
    else {
        cout << "The given graph is not a valid spanning tree.\n";
    }
    return 0;
}