#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>

#define LL long long
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
//7 18 21 25 27 30 32 34 35 37 39 45
/*
3 6
0 2
0 1 1
0 2 1
1 0 1
1 2 1
2 0 1
2 1 1
0 0
*/
// ac : 2

//------------------------------

struct edge_info {
    int start;
    int next;
    LL length;
};

#define MAX_V 500
#define MAX_E 10000
#define INF 5'000'000

int v_size;
int e_size;

int start;
int dest;

std::vector<edge_info> edges;
std::vector<int> graph[MAX_V];
std::vector<int> from_path[MAX_V];

std::vector<LL> distance(MAX_V);
std::vector<bool> disabled_edge(MAX_E);

void check_minus() {
    if(not DEBUG) return;
    PRINT_LINE;
    for(int i = 0; i < v_size; i++) {
        if(distance[i] < 0) std::cout << distance[i] << ' ';
    }
    PRINT_LINE;
}

void input_graph() {
    std::cin >> v_size >> e_size;

    if(v_size == e_size and v_size == 0) exit(0);

    std::cin >> start >> dest;

    int edge_index = 0;
    int u, v;
    LL w;
    REPEAT(e_size) {
        std::cin >> u >> v >> w;
        edges.push_back({u, v, w});
        graph[u].push_back(edge_index++);
    }
}

void find_path() {
    //총 거리, vertex
    std::priority_queue<std::pair<LL, int>> container;

    container.emplace(0, start);
    distance[start] = 0;

    while(not container.empty()) {
        LL cur_length = -container.top().first;
        int cur_v = container.top().second;
        container.pop();

        if(distance[cur_v] < cur_length) continue;

        for(auto edge_idx : graph[cur_v]) {
            if(disabled_edge[edge_idx]) continue;
            auto edge = edges[edge_idx];

            LL new_length = edge.length + cur_length;
            if(new_length > distance[edge.next]) continue;
            else if(new_length < distance[edge.next]) {
                from_path[edge.next].clear();
                from_path[edge.next].push_back(edge_idx);
                distance[edge.next] = new_length;
                container.emplace(-new_length, edge.next);
            }
            else from_path[edge.next].push_back(edge_idx);
        }
    }
}

void disable_path() {
    std::queue<int> container;
    container.push(dest);

    while(not container.empty()) {
        int cur_v = container.front();
        container.pop();

        for(auto e_idx: from_path[cur_v]) {
            if(disabled_edge[e_idx]) continue;
            disabled_edge[e_idx] = true;

            auto edge = edges[e_idx];
            container.push(edge.start);
        }
    }
}

void solve() {
    REPEAT(v_size) {
        graph[_].clear();
        from_path[_].clear();
    }
    edges.clear();
    std::fill(disabled_edge.begin(), disabled_edge.end(), false);
    std::fill(distance.begin(), distance.end(), INF);

    input_graph();
    find_path();



    disable_path();
    std::fill(distance.begin(), distance.end(), INF);
    find_path();


    if(distance[dest] == INF) std::cout << -1 << '\n';
    else std::cout << distance[dest] << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    while(true) {
        solve();
    }

    return 0;
}