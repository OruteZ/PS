#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>

#define LL long long
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)

//------------------------------

#define MAX_V 10000
#define MAX_E 100'000

int v_size;
int e_size;

std::vector<int> graph[MAX_V + 1];
int level[MAX_V + 1];
bool is_cutting_v[MAX_V + 1];
int cur_lv = 0;

void input_graph() {
    std::cin >> v_size >> e_size;
    int u, v;

    REPEAT(e_size) {
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

//return reachable minimum level
int dfs(int v, int from, bool is_root = false) {

    level[v] = ++cur_lv;

    int minimum_lv = level[v];

    int child_cnt=0;
    for(auto next_v : graph[v]) {
        if(next_v == from) continue;
        if(level[next_v] > 0) {
            minimum_lv = std::min(minimum_lv, level[next_v]);
            continue;
        }

        child_cnt++;

        int low = dfs(next_v, v);
        if(not is_root && low >= level[v]) {
            is_cutting_v[v] = true;
        }

        minimum_lv = std::min(minimum_lv, low);
    }

    if(is_root) {
        is_cutting_v[v] = (child_cnt >= 2);
    }

    return minimum_lv;
}

void calculate_cut_vertex() {
    for(int i = 1; i <= v_size; i++) {
        if(level[i] == 0) dfs(i, 0, true);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    input_graph();

    calculate_cut_vertex();

    LL cnt = std::count(is_cutting_v + 1, is_cutting_v + v_size + 1, true);

    std::cout << cnt;
    if(cnt > 0) std::cout << '\n';
    for(int i = 1; i <= v_size; i++) {
        if(is_cutting_v[i]) std::cout << i << ' ';
    }

    return 0;
}