#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<set>

#define LL long long
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX 102
#define ADD_TO_BE_FOOD 50
#define SOURCE 100
#define SINK 101

int graph[MAX][MAX];
int flow[MAX][MAX];
std::set<int> adj[MAX];

int from[MAX];

struct shark_information {
    int size;
    int speed;
    int intelligence;
};

bool operator>(const shark_information& eater, const shark_information& food) {
    bool big_size = eater.size >= food.size;
    bool high_speed = eater.speed >= food.speed;
    bool high_intel = eater.intelligence >= food.intelligence;

    return big_size and high_speed and high_intel;
}

bool operator==(const shark_information& a, const shark_information& b) {
    return a.size == b.size and a.speed == b.speed and a.intelligence == b.intelligence;
}

bool operator>=(const shark_information& a, const shark_information& b) {
    return a > b or a == b;
}

void create_graph(std::vector<shark_information> infos) {
    for(int i = 0; i < infos.size(); i++) {
        for(int j = i + 1; j < infos.size(); j++) {
            int eater, food;
            if(infos[i] >= infos[j]) {
                eater = i;
                food = j + ADD_TO_BE_FOOD;
            }
            else if(infos[j] > infos[i]){
                eater = j;
                food = i + ADD_TO_BE_FOOD;
            }
            else continue;

            graph[eater][food] = 1;
            adj[eater].insert(food);
            adj[food].insert(eater);
        }
    }

    for(int i = 0; i < infos.size(); i++) {
        //connect source
        adj[SOURCE].insert(i);
        adj[i].insert(SOURCE);

        graph[SOURCE][i] = 2;

        //connect with sink
        int j = i +ADD_TO_BE_FOOD;
        adj[SINK].insert(j);
        adj[j].insert(SINK);

        graph[j][SINK] = 1;
    }
}

bool bfs(int start, int dest, int& total_flow) {
    for(int& i : from) i = -1;

    std::queue<int> q;

    q.push(start);
    from[start] = start;
    while(not q.empty()) {
        int cur = q.front(); q.pop();

        for(auto next : adj[cur]) {
            if(from[next] != -1) continue;
            if(flow[cur][next] >= graph[cur][next]) continue;

            from[next] = cur;
            q.push(next);

            if(next == dest) goto FLOW_WATER;
        }
    }

    FLOW_WATER:
    if(from[dest] == -1) return false;

    int flow_value = INT32_MAX;
    for(int i = dest; i != start; i = from[i]) {
        flow_value = std::min(flow_value, graph[from[i]][i] - flow[from[i]][i]);
    }

    for(int i = dest; i != start; i = from[i]) {
        flow[from[i]][i] += flow_value;
        flow[i][from[i]] -= flow_value;
    }

    total_flow += flow_value;
    return true;
}

int get_maximum_flow() {
    int ret = 0;
    while(true) {
        if(not bfs(SOURCE, SINK, ret)) break;
    }

    return ret;
}

void print_graph(int start) {
    bool visited[MAX] = {false};

    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while(not q.empty()) {
        int cur = q.front();
        q.pop();

        for(auto next : adj[cur]) {
            if(visited[next]) continue;
            if(graph[cur][next] == 0) continue;

            visited[next] = true;
            q.push(next);

            std::cout << cur << ' ' << next << ' ' << graph[cur][next] << ' ' << flow[cur][next] << '\n';
        }
    }
}

int main() {
    FAST_IO;
    int n; std::cin >> n;

    std::vector<shark_information> infos(n);
    for(auto &info : infos) {
        std::cin >> info.size >> info.speed >> info.intelligence;
    }

    create_graph(infos);
    int max_flow = get_maximum_flow();

    std::cout << n - max_flow << std::endl;

//    print_graph(SOURCE);
}