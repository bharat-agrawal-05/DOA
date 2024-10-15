#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#define INF numeric_limits<double>::max()
using namespace std;

pair<vector<vector<double>>, double> Prim(vector<vector<double>>& adj) {
    int n = adj.size();
    vector<vector<double>> mstEdges;
    double mstWt = 0;
    vector<bool> visited(n, 0);
    priority_queue<vector<double>, vector<vector<double>>, greater<vector<double>>> pq;
    pq.push({0, 0, -1});

    while (!pq.empty()) {
        double wt = pq.top()[0];
        double node = pq.top()[1];
        double parent = pq.top()[2];
        pq.pop();

        if (visited[node]) {
            continue;
        }
        visited[node] = 1;

        if (parent != -1) {
            mstEdges.push_back({parent, node, wt});
            mstWt += wt;
        }

        for (double i = 0; i < n; ++i) {
            if (i != node && adj[node][i] != INF && !visited[i]) {
                pq.push({adj[node][i], i, node});
            }
        }
    }
    return {mstEdges, mstWt};
}

int main() {
    int n, m;
    cout << "Enter the number of vertices : ";
    cin >> n;
    vector<vector<double>> adj(n, vector<double>(n, INF));
    cout << "Enter the number of edges : ";
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cout << "Enter an edge : ";
        double u, v, wt;
        cin >> u >> v >> wt;
        adj[u][v] = adj[v][u] = wt;
    }

    for (int i = 0; i < n; ++i) {
        adj[i][i] = 0;
    }

    pair<vector<vector<double>>, double> mst = Prim(adj);
    cout << "The minimum spanning tree is : \n";
    for (auto edge: mst.first) {
        cout << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
    }
    cout << "The weight of the minimum spanning tree is : " << mst.second << "\n";
    return 0;
}