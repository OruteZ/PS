#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> values;
vector<vector<int>> tree;

// {depth, node}
vector<pair<int, int>> depth_info;

// dp[i] = i번째 노드를 루트로 하는 서브트리의 계산 최댓값, 그리고 그 값을 구성하는 노드들의 번호
vector<pair<int, vector<int>>> dp;

int main() {
    int v_cnt; cin >> v_cnt;

    values.resize(v_cnt);
    tree.resize(v_cnt);
    depth_info.resize(v_cnt);

    vector<bool> visited(v_cnt, false);
    for (int i = 0; i < v_cnt; i++) {
        cin >> values[i];
    }
    visited[0] = true;

    for (int i = 0; i < v_cnt - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;

        if (visited[u]) {
            tree[u].push_back(v);
            depth_info[v] = {depth_info[u].first + 1, v};
            visited[v] = true;
        } else {
            tree[v].push_back(u);
            depth_info[u] = {depth_info[v].first + 1, u};
            visited[u] = true;
        }
    }

    // sort by depth
    sort(depth_info.begin(), depth_info.end(), greater<>());

    //debug
    // for (auto& [depth, node] : depth_info) {
    //     cout << depth << " " << node + 1 << endl;
    // }

    // build dp
    dp.resize(v_cnt);
    for (int i = 0; i < v_cnt; i++) {
        int node = depth_info[i].second;
        int depth = depth_info[i].first;

        // leaf node
        if (tree[node].empty()) {
            dp[node] = {values[node], {node}};
            continue;
        }

        int include_node = values[node];
        vector<int> include_nodes = {node};
        for (int child : tree[node]) {
            for (int grand_child : tree[child]) {
                    include_node += dp[grand_child].first;
                    include_nodes.insert(include_nodes.end(), dp[grand_child].second.begin(), dp[grand_child].second.end());
            }
        }

        int exclude_node = 0;
        vector<int> exclude_nodes;
        for (int child : tree[node]) {
            exclude_node += dp[child].first;
            exclude_nodes.insert(exclude_nodes.end(), dp[child].second.begin(), dp[child].second.end());
        }

        if (include_node > exclude_node) {
            dp[node] = {include_node, include_nodes};
        } else {
            dp[node] = {exclude_node, exclude_nodes};
        }
    }

    // print answer
    cout << dp[0].first << endl;
    sort(dp[0].second.begin(), dp[0].second.end());
    for (int node : dp[0].second) {
        cout << node + 1 << " ";
    }
    cout << endl;
    
    return 0;
}