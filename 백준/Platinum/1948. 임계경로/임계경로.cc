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


#define MAX 10000
#define MAX_EDGE 100'000

struct edge_info {
public:
    int index;
    int start;
    int dest;
    int length;

    bool operator<(const edge_info& other) const {
        return index < other.index;
    }
};

// namespace std {
//     template <>
//     struct hash<edge_info> {
//         size_t operator()(const edge_info& t) const {
//             hash<int> hash_func;

//             return t.index ^ (hash_func(t.length));
//         }-2 -1 1 2 3 4 7 8 9
//     };
// }

LL distance[MAX + 1] = {0};
int order[MAX + 1] = {0};
std::vector<int> r_order(MAX + 1);
std::vector<edge_info> edges;
std::vector<int> neighbor[MAX + 1];
std::vector<int> from_edge[MAX_EDGE];

void input_graph(int m) {
    int u, v, w;
    int i = 0;
    REPEAT(m) {
        std::cin >> u >> v >> w;
        edges.push_back({i++, u,v, w});
        neighbor[u].push_back(i - 1);
        order[v]++;
    }
}

LL find_path(int start, int last) {
    std::queue<int> container;

    container.push(start);

    while(not container.empty()) {
//        std::cout << container.size() << std::endl;
        int current = container.front();
        container.pop();

        for(auto edge_idx : neighbor[current]) {
            auto edge = edges[edge_idx];
            LL new_distance = edge.length + distance[current];

            order[edge.dest]--;
            if(order[edge.dest] == 0) container.push(edge.dest);

            if(distance[edge.dest] > new_distance) continue;
            if(distance[edge.dest] < new_distance) from_edge[edge.dest].clear();

            from_edge[edge.dest].push_back(edge_idx);
            distance[edge.dest] = new_distance;
        }
    }

    return distance[last];
}

LL back_on_road(int last) {
    std::queue<int> container;
    bool visited[MAX_EDGE];

    container.push(last);

    LL cnt = 0;

    while(not container.empty()) {
        auto cur = container.front();
        container.pop();

        for(int edge_idx : from_edge[cur]) {
            if(visited[edge_idx]) continue;
            visited[edge_idx] = true;

            cnt++;
            container.push(edges[edge_idx].start);
        }
    }

    return cnt;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n, m; std::cin >> n >> m;
    input_graph(m);

    int start, last; std::cin >> start >> last;
    auto length = find_path(start, last);
    auto roads = back_on_road(last);

    std::cout << length << ' ' << roads << '\n';
    return 0;
}