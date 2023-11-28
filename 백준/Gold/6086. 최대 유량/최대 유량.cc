#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>

#define LL long long
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX_V 100

int graph[MAX_V][MAX_V] = {0, };
int flow[MAX_V][MAX_V] = {0, };
bool connected[MAX_V][MAX_V] = {0, };

int from[MAX_V];

bool bfs(int start, int end, int& total_flow) {
    for(int& i : from) i = -1;

    std::queue<int> q;
    q.push(start);
    from[start] = start;

    while(not q.empty()) {
        int cur = q.front();
        q.pop();

        for(int next = 0; next < MAX_V; next++) if(next != cur) {
            if(not connected[cur][next]) continue;
            if(from[next] != -1) continue; //visited;
            if(flow[cur][next] >= graph[cur][next]) continue; //full

            from[next] = cur;
            q.push(next);

            if(next == end) break;
        }
    }

    if(from[end] == -1) return false;

    int flow_value = INT32_MAX;
    for(int i = end; i != start; i = from[i]) {
        flow_value = std::min(flow_value, graph[from[i]][i] - flow[from[i]][i]);
    }

    for(int i = end; i != start; i = from[i]) {
        flow[from[i]][i] += flow_value;
        flow[i][from[i]] -= flow_value;
    }

    total_flow += flow_value;
    return true;
}

int main() {
    FAST_IO;
    int e; std::cin >> e;

    char u, v; int w;
    REPEAT(e) {
        std::cin >> u >> v >> w;
        if(u == v) continue;

        int u_num = u - 'A';
        int v_num = v - 'A';
        graph[u_num][v_num] += w;
        graph[v_num][u_num] += w;

        connected[u_num][v_num] = connected[v_num][u_num] = true;
    }

    int start = 0;
    int dest = 'Z' - 'A';
    int answer = 0;

    while(true) { //BFS 자체를 증가 경로가 없을 때 까지 반복
        if(not bfs(start, dest, answer)) break;
    }

    std::cout << answer << '\n';

    return 0;
}