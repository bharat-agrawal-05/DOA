// I am considering directed graph

#include <iostream>
#include <vector>
using namespace std;

bool bellmanFord(vector<vector<double>> &edges, int n, int src, vector<double> &dist) {
    dist[src] = 0;
    for (int i = 1; i <= n - 1; ++i) {
        for (auto edge: edges) {
            double u = edge[0];
            double v = edge[1];
            double wt = edge[2];
            if (dist[u] == 1e9) {
                continue;
            }
            if (dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    bool hasNegCycle = false;
    for (auto edge: edges) {
        double u = edge[0];
        double v = edge[1];
        double wt = edge[2];
        if (dist[u] == 1e9) {
            continue;
        }
        if (dist[u] + wt < dist[v]) {
            hasNegCycle = true;
            break;
        }
    }

    return hasNegCycle;
}

int main() {
    int n, src;
    cout << "Enter the number of cities: ";
    cin >> n;
    cout << "Enter the source: ";
    cin >> src;

    int e;
    cout << "Enter the number of edges: ";
    cin >> e;
    cout << "Enter the edges: " << endl;
    vector<vector<double>> edges;
    for (int i = 0; i < e; i++) {
        double u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<double> dist(n, 1e9);
    bool hasNegCycle = bellmanFord(edges, n, src, dist);
    if (hasNegCycle) {
        cout << "Graph has negative cycle" << endl;
        return 0;
    }

    cout << "Source City = " << src << endl;
    for (int i = 0; i < n; i++) {
        if (dist[i] == 1e9) {
            cout << "City " << i << " = " << "∞" << endl;
        }
        else {
            cout << "City " << i << " = " << dist[i] << endl;
        }
    }
    return 0;
}