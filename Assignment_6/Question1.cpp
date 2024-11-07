// I am using 0 based indexing for numbering the cities

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<double> djikstra(vector<vector<pair<int, double>>> &graph, int src) {
    int n = graph.size();
    vector<double> dist(n, 1e9);
    vector<bool> visited(n, 0);

    dist[src] = 0;
    // <distance, city number>
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        double dis = pq.top().first;
        int city = pq.top().second;
        pq.pop();

        for (auto adj: graph[city]) {
            int v = adj.first;
            double w = adj.second;
            if (dist[v] > dist[city] + w) {
                dist[v] = dist[city] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n, src;
    cout << "Enter the number of cities: ";
    cin >> n;
    cout << "Enter the source: ";
    cin >> src;
    vector<vector<pair<int, double>>> graph(n, vector<pair<int, double>>());
    int e;
    cout << "Enter the number of edges: ";
    cin >> e;
    cout << "Enter the edges: " << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<double> dist = djikstra(graph, src);
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

/*
7
0
11
0 1 3
0 2 2
1 2 2
1 3 1
2 3 3
1 4 4
4 5 1
3 5 2
2 5 6
2 6 5
5 6 2

0 3 2 4 7 6 7
*/