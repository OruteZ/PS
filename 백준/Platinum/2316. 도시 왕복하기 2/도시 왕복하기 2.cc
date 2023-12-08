#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<set>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX 400
#define INF 100'000

std::vector<int> adj[MAX * 2 + 1];
int from[MAX * 2 + 1];

int capacity[MAX * 2 + 1][MAX * 2 + 1];
int flow[MAX * 2 + 1][MAX * 2 + 1];

void slip(int start, int dest, int &total_flow)     {
    int flow_value = INT32_MAX;
    for(int i = dest; i != start; i = from[i]) {
        flow_value = std::min(flow_value, capacity[from[i]][i] - flow[from[i]][i]);
    }

    for(int i = dest; i != start; i = from[i]) {
        flow[from[i]][i] += flow_value;
        flow[i][from[i]] -= flow_value;
    }

    total_flow += flow_value;
}

bool try_find_route(int start, int dest, int &total_flow) {
    for(int &i : from) i = -1;

    std::queue<int> q;
    q.push(start);
    from[start] = start;

    while(not q.empty()) {
        int cur = q.front();
        q.pop();

        for(int next : adj[cur]) {
            if(from[next] != -1) continue;
            if(flow[cur][next] == capacity[cur][next]) continue;

            from[next] = cur;
            q.push(next);

            if(next == dest) {
                slip(start, dest, total_flow);
                return true;
            }
        }
    }

    return false;
}

int main() {
    FAST_IO;

    int n, p;
    std::cin >> n >> p;
    for(int i = 1; i <= n; i++) {
        int in = i, out = i + MAX;
        capacity[in][out] = 1;

        adj[in].push_back(out);
        adj[out].push_back(in);
    }

    REPEAT(p) {
        int u, v;
        std::cin >> u >> v;

        int u_input = u, u_output = u + MAX;
        int v_input = v, v_output = v + MAX;

        capacity[v_output][u_input] = INF;
        capacity[u_output][v_input] = INF;

        adj[u_output].push_back(v_input);
        adj[v_input].push_back(u_output);

        adj[v_output].push_back(u_input);
        adj[u_input].push_back(v_output);
    }

    int start = 1 + MAX, dest = 2, total_flow = 0;
    while(true) {
        if(not try_find_route(start, dest, total_flow))
            break;
    }

    std::cout << total_flow;
}