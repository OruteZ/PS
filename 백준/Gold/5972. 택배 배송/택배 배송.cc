#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
	cin >> N >> M;
    vector<vector<pair<int,int>>> graph(N+1);
    for (int i = 0; i < M; ++i) {
        int A, B, C; cin >> A >> B >> C;
        graph[A].emplace_back(B, C);
        graph[B].emplace_back(A, C);
    }
	
    vector<int> dist(N+1, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[1] = 0;
    pq.emplace(0, 1); // {cost, node}

    while (not pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost != dist[u]) continue;     
        if (u == N) break;

        for (auto [v, w] : graph[u]) {
            int nc = cost + w;
            if (nc < dist[v]) {
                dist[v] = nc;
                pq.emplace(nc, v);
            }
        }
    }

    cout << dist[N] << '\n';
    return 0;
}
