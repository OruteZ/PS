#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr ll INF = 4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<ll> dist(N + 1), weather(M + 1);
    
    for (int i = 1; i <= N; i++) cin >> dist[i];
    for (int d = 1; d <= M; d++) cin >> weather[d];


    vector<ll> prev(N + 1, INF), cur(N + 1, INF);
    prev[0] = 0;

    for (int d = 1; d <= M; d++) {
        cur = prev;

        // 이동: 하루에 도시를 하나만 더 진행 가능
        int up = min(N, d);
        for (int c = 1; c <= up; c++) {
            if (prev[c - 1] == INF) continue;
            ll cost = prev[c - 1] + dist[c] * weather[d];
            
            if (cost < cur[c]) cur[c] = cost;
        }

        prev.swap(cur);
    }

    cout << prev[N] << "\n";
    return 0;
}
