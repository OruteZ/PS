#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<list>
#include<map>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

using namespace std;
//-----------------------------

//==========data============
struct course {
    int from;
    int to;
    LL len;
};

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

int N, M, K, S, T;
vector<course> courses;
vector<vector<PII>> graph;

void build_graph() {
    graph.resize(N + 1);
    for(auto& c : courses) {
        graph[c.from].emplace_back(c.to, c.len);
        graph[c.to].emplace_back(c.from, -1);
    }
}


unordered_map<PII, LL, pair_hash> dp;

//리프트를 k_cnt번 탄, node 지점에서 목적지까지 얼마나 더 가야 하는가?
LL get_dist(int node, int k_cnt) {
    if(node == T and k_cnt == K) return 0;

    if(dp.find({node, k_cnt}) == dp.end()) {
        dp[{node, k_cnt}] = -100; // -100 : 초기화 되어 본적이 없음
    }

    LL& ret = dp[{node, k_cnt}];
    if(ret != -100) return ret;

    ret = -1;

    //get dp
    for(auto& [next, dist] : graph[node]) {
        if(dist != -1) {
            LL d = get_dist(next, k_cnt);
            // return 값이 -1이다 : 목적지에 도달할 수 없다
            if(d == -1) continue;

            ret = max(ret, d+dist);
        }

        // dist가 -1이다 : 부모 정점이다 == 리프트로 타고 올라갈 수 있다
        else if(k_cnt < K) {
            ret = max(ret, get_dist(next, k_cnt + 1));
        }
    }

    return ret;
}

int main() {
    cin >> N >> M >> K >> S >> T;

    courses.resize(M);
    for(auto& c : courses) {
        cin >> c.from >> c.to >> c.len;
    }

    build_graph();

    LL result = get_dist(S, 0);
    cout << result << endl;
}
