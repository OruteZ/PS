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

int new_id = 0;

int v_size, e_size;
std::vector<int> graph[MAX_V + 1];
int id[MAX_V + 1];
bool is_group_id[MAX_V + 1];
std::stack<int> stk;

void input_graph(int size) {
    int a, b;
    REPEAT(size) {
        std::cin >> a >> b;
        graph[a].push_back(b);
    }
}

bool visited(int v) {
    return id[v] > 0;
}

int get_group_id(int cur_v, std::vector<std::vector<int>>& scc) {
    if(visited(cur_v)) return id[cur_v];
    id[cur_v] = ++new_id;
    stk.push(cur_v);

    int group_id = id[cur_v];
    for(int next_v : graph[cur_v]) {
        int next_id = get_group_id(next_v, scc);
        if(is_group_id[next_id]) continue;

        group_id = std::min(next_id, group_id);
    }

    if(group_id == id[cur_v]) {
        is_group_id[id[cur_v]] = true;
        std::vector<int> group;
        while(true) {
            int target_v = stk.top();
            stk.pop();

            group.push_back(target_v);
            id[target_v] = id[cur_v];
            if(target_v == cur_v) break;
        }

        scc.push_back(group);
    }

    return group_id;
}

std::vector<std::vector<int>> get_scc() {
    std::vector<std::vector<int>> scc;

    for(int i = 1; i < v_size; i++) {
        get_group_id(i, scc);
    }

    for(auto& group : scc) {
        std::sort(group.begin(), group.end());
    }
    std::sort(scc.begin(), scc.end());

    return scc;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> v_size >> e_size;
    input_graph(e_size);

    auto scc = get_scc();

    //print
    std::cout << scc.size() << '\n';
    for(const auto& group : scc) {
        for(int number : group) std::cout << number << ' ';
        std::cout << -1 << '\n';
    }

    return 0;
}