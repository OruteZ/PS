#include<bits/stdc++.h>

using namespace std;

struct wolf_dijk_info {
    int dist;
    int u;
    bool fast;

    //construct
    wolf_dijk_info(int dist, int u, bool fast) : dist(dist), u(u), fast(fast) {}
};

struct w_compare {
    bool operator()(const wolf_dijk_info &a, const wolf_dijk_info &b) {
        if(a.dist == b.dist) {
            if(not a.fast and b.fast) {
                return true;
            } 
            else {
                return false;
            }
        }
        return a.dist > b.dist;
    }
};

vector<int> dijk_wolf(
    const vector<vector<int>> &dist,
    const map<int, vector<int>> &graph,
    int start
) {
    vector<vector<int>> result(dist.size(), vector<int>(2, 1e9));

    result[start][false] = 0;

    priority_queue<wolf_dijk_info, vector<wolf_dijk_info>, w_compare> pq;
    pq.emplace(0, start, false);

    while (not pq.empty()) {
        wolf_dijk_info info = pq.top();
        int d = info.dist;
        int u = info.u;
        bool fast = info.fast;

        pq.pop();

        if (d > result[u][fast]) {
            continue;
        }

        for (auto v : graph.at(u)) {
            // 빠르게 달려왔을 경우 : 경로의 길이 * 2
            if (fast and result[v][false] > result[u][true] + dist[u][v] * 2) {
                result[v][false] = result[u][true] + dist[u][v] * 2;
                pq.emplace(result[v][false], v, false);
            }

            // 느리게 달려왔을 경우 : 경로의 길이 / 2
            if (not fast and result[v][true] > result[u][false] + dist[u][v] / 2) {
                result[v][true] = result[u][false] + dist[u][v] / 2;
                pq.emplace(result[v][true], v, true);
            }
        }
    }

    vector<int> ret(dist.size());
    for (int i = 0; i < dist.size(); i++) {
        ret[i] = min(result[i][false], result[i][true]);
    }
    return ret;
}

vector<int> dijk(
    const vector<vector<int>> &dist,
    const map<int, vector<int>> &graph,
    int start
) {
    vector<int> result(dist.size(), 1e9);
    result[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    while (not pq.empty()) {
        pair<int, int> info = pq.top();
        int d = info.first;
        int u = info.second;
        pq.pop();

        if (d > result[u]) {
            continue;
        }

        for (auto v : graph.at(u)) {
            if (result[v] > result[u] + dist[u][v]) {
                result[v] = result[u] + dist[u][v];
                pq.emplace(result[v], v);
            }
        }
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, 1e9));
    map<int, vector<int>> graph;

    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        dist[u][v] = w * 2;
        dist[v][u] = w * 2;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    //=================

    vector<int> wolf = dijk_wolf(dist, graph, 1);
    vector<int> fox = dijk(dist, graph, 1);

    // cout << "Finished dijkstra" << endl;

    int answer = 0;
    // cout << "Compare wolf and fox" << endl;
    for(int i = 1; i <= n; i++) {
        // cout << " " << wolf[i] << " " << fox[i] << endl;

        if(wolf[i] > fox[i]) {
            answer++;
        }
    }
    // cout << "Finished compare" << endl;
    cout << answer;

    return 0;
}