#include <bits/stdc++.h>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

using namespace std;
//-----------------------------
int V, E;
vector<vector<int>> graph;
vector<int> group_num;

void input_graph() {
    int u, v;
    REPEAT(E) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

bool dfs(int node, int cur_group) {
    if(group_num[node] == 1 - cur_group) return false;
    if(group_num[node] == cur_group) return true;

    group_num[node] = cur_group;

    for(int adj: graph[node]) {
        bool result = dfs(adj, 1 - cur_group);
        if(not result) return false;
    }

    return true;
}

void solve() {
    cin >> V >> E;
    graph.assign(V + 1, vector<int>(0));
    group_num.assign(V + 1, -1);

    input_graph();

    if(DEBUG) cout << "start dfs : " << ENDL;

    bool ret = true;
    for(int i = 1; i <= V; i++) {
        if(group_num[i] != -1) continue;
        
        bool recur = dfs(i, 0);
        if(!recur) {
            ret = false;
            break;
        }    
    }

    if(DEBUG) for(int i = 1; i < V + 1; i++) {
        cout << "   group " << i << " : " << group_num[i] << ENDL;
    }

    cout << (ret ? "YES" : "NO") << ENDL;
}


int main() {
    int t_case;
    cin >> t_case;

    while(t_case--) {
        solve();
    }
}
