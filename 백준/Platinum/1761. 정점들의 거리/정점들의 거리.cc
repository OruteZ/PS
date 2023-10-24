#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>

#pragma region MACRO

#define LL long long
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)

#pragma endregion

#define MAX_N 40000
#define MAX_M 10000

int n, m;

std::vector<std::pair<int, int>> neighbor_dist[MAX_N + 1];

std::vector<std::pair<int, int>> parent_dist(MAX_N + 1);
std::vector<int> depth(MAX_N + 1);

void initialize_tree(int target, int p, int dist) {
    parent_dist[target] = std::make_pair(p, dist);
    if(target == p) depth[target] = 1;
    else depth[target] = depth[p] + 1;

    for(const auto &child : neighbor_dist[target]) {
        if(child.first == parent_dist[target].first) continue;
        if(child.first == target) continue;

        initialize_tree(child.first, target, child.second);
    }
}

LL go_up(int& x) {
    auto parent = parent_dist[x];
    x = parent.first;

    return parent.second;
}

LL get_dist(int a, int b) {
    LL result = 0;

    if(depth[a] < depth[b]) std::swap(a, b);

    while(depth[a] > depth[b]) result += go_up(a);

    while(a != b) {
        result += go_up(a);
        result += go_up(b);
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int a, b, length;

    std::cin >> n;
    REPEAT(n - 1) {
        std::cin >> a >> b >> length;

        neighbor_dist[a].emplace_back(b, length);
        neighbor_dist[b].emplace_back(a, length);
    }

    initialize_tree(1, 1, 0);

    std::cin >> m;
    REPEAT(m) {
        std::cin >> a >> b;

        std::cout << get_dist(a, b) << '\n';
    }

    return 0;
}