#include<bits/stdc++.h>

using namespace std;

vector<int> dijkstra(int start, vector<vector<int>>& dist, map<int, vector<int>>& graph) {
    vector<int> ret(dist.size(), 1e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.emplace(0, start);
    ret[start] = 0;

    while(!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if(ret[cur] < cur_dist) {
            continue;
        }

        for(int next : graph[cur]) {
            int next_dist = cur_dist + dist[cur][next];

            if(ret[next] > next_dist) {
                ret[next] = next_dist;
                pq.emplace(next_dist, next);
            }
        }
    }

    return ret;
}

void solve() {
    int n, m, t;
    int s, g, h;

    cin >> n >> m >> t;
    cin >> s >> g >> h;

    map<int, vector<int>> graph;
    vector<vector<int>> dist(n+1, vector<int>(n+1, -1));

    int a, b, d;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> d;

        graph[a].push_back(b);
        graph[b].push_back(a);
        dist[a][b] = d;
        dist[b][a] = d;
    }

    vector<int> target(t);
    for(int i = 0; i < t; i++) {
        cin >> target[i];
    }

    vector<int> s_to_target = dijkstra(s, dist, graph);
    vector<int> g_to_target = dijkstra(g, dist, graph);
    vector<int> h_to_target = dijkstra(h, dist, graph);

    sort(target.begin(), target.end());
    for(int pos : target) {
        int s_to_pos = s_to_target[pos];
        int s_to_g = s_to_target[g];
        int s_to_h = s_to_target[h];
        int g_to_pos = g_to_target[pos];
        int h_to_pos = h_to_target[pos];

        int route1 = s_to_g + dist[g][h] + h_to_pos;
        int route2 = s_to_h + dist[h][g] + g_to_pos;
        int origin_route = s_to_pos;

        if(s_to_pos == min(route1, route2)) {
            cout << pos << " ";
        } 
    }
    cout << '\n';
}

int main() {
    int t_case;
    cin >> t_case;

    while(t_case--) {
        solve();
    }
}