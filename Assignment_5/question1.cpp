#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSet {
    vector<int> parent, rank;

    public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int findUltimateParent(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = findUltimateParent(parent[x]);
        return parent[x];
    }

    void unionByRank(int u, int v) {
        int pu = findUltimateParent(u);
        int pv = findUltimateParent(v);
        if (pu == pv) {
            return ;
        }
        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        else {
            parent[pu] = pv;
            rank[pv]++;
        }
    }
};

bool comparator(vector<double>& a, vector<double>& b) {
    return a[2] < b[2];
}

pair<vector<vector<double>>, double> Kruskal(vector<vector<double>>& edges, int n) {
    sort(edges.begin(), edges.end(), comparator);
    DisjointSet ds(n);
    vector<vector<double>> mstEdges;
    double mstWt = 0;
    for (auto edge: edges) {
        double u, v, wt;
        u = edge[0];
        v = edge[1];
        wt = edge[2];
        if (ds.findUltimateParent(u) != ds.findUltimateParent(v)) {
            mstEdges.push_back({u, v, wt});
            mstWt += wt;
            ds.unionByRank(u, v);
        }
    }
    return {mstEdges, mstWt};
}

int main() {
    int n, m;
    cout << "Enter the number of vertices : ";
    cin >> n;
    cout << "Enter the number of edges : ";
    cin >> m;
    vector<vector<double>> edges;
    for (int i = 0; i < m; ++i) {
        cout << "Enter an edge : ";
        double u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }

    pair<vector<vector<double>>, double> mst = Kruskal(edges, n);
    cout << "The minimum spanning tree is : \n";
    for (auto edge : mst.first) {
        cout << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
    }
    cout << "The weight of the minimum spanning tree is : " << mst.second << "\n";
    return 0;
}