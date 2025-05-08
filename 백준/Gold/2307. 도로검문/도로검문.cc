#include <bits/stdc++.h>
using namespace std;
using ll = int;
const ll INF = (ll)1e18;

struct Edge {
    int to;
    int id;
    int w;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<Edge>> adj(N+1);
    for(int i = 0; i < M; i++){
        int a, b, t;
        cin >> a >> b >> t;
        adj[a].push_back({b, i, t});
        adj[b].push_back({a, i, t});
    }

    // 다익스트라 함수 (제외할 간선 ID = ban_id)
    auto dijkstra = [&](int ban_id, vector<int>* outPrevEdge = nullptr){
        vector<ll> dist(N+1, INF);
        vector<int> prevEdge(N+1, -1);
        dist[1] = 0;
        // min-heap: (현재거리, 정점)
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
        pq.emplace(0, 1);

        while(not pq.empty()){
            auto [d,u] = pq.top(); pq.pop();
            if(d > dist[u]) continue;
            if(u == N) break;  // N번 도착하면 종료해도 무방
            for(auto &e : adj[u]){
                if(e.id == ban_id) continue;
                ll nd = d + e.w;
                if(nd < dist[e.to]){
                    dist[e.to] = nd;
                    prevEdge[e.to] = e.id;
                    pq.emplace(nd, e.to);
                }
            }
        }
        if(outPrevEdge) {
            *outPrevEdge = prevEdge;
        }
        return dist[N];
    };

    // 1) 원래 최단 거리, prevEdge 정보 얻기
    vector<int> prevEdge;
    ll D = dijkstra(-1, &prevEdge);
    if(D == INF){
        // 사실 입력 조건상 연결 보장됨
        cout << "-1\n";
        return 0;
    }

    // 2) 최단 경로 위의 간선 ID들 복원
    vector<int> pathEdges;
    int cur = N;
    while(cur != 1){
        int eid = prevEdge[cur];
        pathEdges.push_back(eid);
        // eid 간선의 양 끝을 찾아서 이전 정점을 구해야 함
        // 편하게: adj 에서 eid가 남은 쪽의 to가 cur이 아니면 그쪽이 prev 정점
        int pu = -1;
        for(auto &e : adj[cur]){
            if(e.id == eid){
                pu = e.to;
                break;
            }
        }
        cur = pu;
    }
    // pathEdges 에는 N→1 역순으로 저장됐으니, 순서는 상관없음

    // 3) 각각의 간선을 검문(제거)했을 때 지연량 계산
    ll ans = 0;
    for(int eid : pathEdges){
        ll d2 = dijkstra(eid);
        if(d2 == INF){
            cout << "-1\n";
            return 0;
        }
        ans = max(ans, d2 - D);
    }

    cout << ans << "\n";
    return 0;
}
