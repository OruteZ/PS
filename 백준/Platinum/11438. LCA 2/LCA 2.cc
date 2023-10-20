#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>

#define MAX 100'001
#define MAX_DEPTH 18
#define DEBUG1 false
#define DEBUG2 false
#define REPEAT(n) for(int _ = 0; _ < n; _++)
typedef long long ll;

int parents[MAX + 1][MAX_DEPTH + 1] = {0};
std::vector<int> link[MAX + 1];
int depth[MAX + 1] = {0};
int n, m;

bool is_connected(int idx) {
    if(idx == 1) return true;
    return parents[idx][0] != 0;
}

void init(int parent, int child) {
    parents[child][0] = parent;
    depth[child] = depth[parent] + 1;

    for(int i = 1; i <= MAX_DEPTH; i++) {
        int ith_parent = parents[parents[child][i - 1]][i - 1];
        if(ith_parent == 0) break;

        parents[child][i] = ith_parent;
    }

    for(auto next : link[child]) {
        if(next == child) continue;
        if(next == parent) continue;

        init(child, next);
    }
}

int lca(int a, int b) {
    if(DEBUG1) std::cout << "Start Finding LCA" << std::endl;

    if(a == 1 or b == 1) return 1;

    if(depth[a] < depth[b]) std::swap(a, b);

    //depth 통일, 이렇게 하는거 신기함
    if(depth[a] != depth[b]) {
        if(DEBUG1) std::cout << "DEPTH is diff" << '\n';
        if(DEBUG1) std::cout << "depth a : " << depth[a] << " depth b : " << depth[b] << '\n';

        for(int i = MAX_DEPTH; i >= 0; i--) {
            if(depth[parents[a][i]] >= depth[b]) {
                a = parents[a][i];
            }
        }
        if(DEBUG1) {
            std::cout << ". . . " << "\n";
            std::cout << "FInish depth same" << '\n';
            std::cout << "depth a : " << depth[a] << " depth b : " << depth[b] << '\n';
        }
    }

    if(DEBUG1) std::cout << "a = " << a << ", b = " << b << std::endl;

    if(a == b) return a;
    for(int i = MAX_DEPTH; i >= 0; i--) {
        if(parents[a][i] != parents[b][i]) {
            a = parents[a][i];
            b = parents[b][i];

            if(DEBUG1) {
                std::cout << a << " " << b << '\n';
            }
        }
    }

    return parents[a][0];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    depth[1] = 1;
    std::cin >> n;

    int a, b;
    REPEAT(n-1) {
        std::cin >> a >> b;
        link[a].push_back(b);
        link[b].push_back(a);
    }


    init(0, 1);

    if(DEBUG2) {
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= MAX_DEPTH; j++) {
                std::cout << parents[i][j] << " ";
            }
            std::cout << '\n';
        }
    }

    std::cin >> m;
    REPEAT(m) {
        std::cin >> a >> b;

        std::cout << lca(a, b) << '\n';
    }

    return 0;
}