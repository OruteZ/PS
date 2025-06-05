#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N+1);
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // 1번 정점에서 BFS를 통해 최단 거리(깊이) 계산
    vector<int> dist(N+1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);

    while(not q.empty()){
        int u = q.front();
        q.pop();
        for(int w : adj[u]) {
            if(dist[w] == -1) {
                dist[w] = dist[u] + 1;
                q.push(w);
            }
        }
    }

    // 깊이별 정점 개수 세기
    int maxDepth = 0;
    for(int v = 1; v <= N; v++){
        maxDepth = max(maxDepth, dist[v]);
    }

    vector<ll> cnt(maxDepth + 1, 0);
    for(int v = 1; v <= N; v++){
        cnt[dist[v]]++;
    }


    ll ans = 2;  // 2 = 1번지점에 배치/배치하지 않음 경우의 수
    for(int d = 1; d <= maxDepth; d++){
        ll ways = (1 + cnt[d]) % MOD;
        ans = (ans * ways) % MOD;
    }

    // “한 대도 배치하지 않는(공집합)” 경우를 빼준다.
    ans = (ans - 1);
    if(ans < 0) ans += MOD;

    cout << ans << "\n";
    return 0;
}
