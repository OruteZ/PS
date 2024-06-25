#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>
#include<map>

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

class MaximumFlowProbSolver {
private:
    int size{};
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> flow;
    std::vector<std::vector<int>> capacity;
    std::vector<int> from;
    int n, m, k;
    int ret = 0;

    static void resize_2d(std::vector<std::vector<int>>& vec, int n, int m) {
        vec.resize(n);
        for(std::vector<int>& v : vec) v.resize(m);
    }

    void single_flow(int source, int sink) {
        for(int& i : from) i = -1;

        std::queue<int> container;
        from[source] = source;
        container.push(source);

        while(not container.empty() && from[sink] == -1) {
            auto cur = container.front();
            container.pop();

            for(int next : graph[cur]) {
                if(from[next] != -1) continue; //visited

                int available_cap = (capacity[cur][next] - flow[cur][next]);
                if(available_cap > 0) {
                    container.push(next);
                    from[next] = cur;
                }
            }
        }
    }

    static void fill(vector<int>& vec, int value = 0) {
        for(int&i : vec) i = value;
    }

    void connect(int u, int v, int cap) {
        graph[u].push_back(v);
        graph[v].push_back(u);
        capacity[u][v] = cap;
    }
public:
    void init(int new_size) {
        this->size = new_size;

        graph.resize(new_size);
        from.resize(new_size); fill(from, -1);

        resize_2d(flow, new_size, new_size);
        for(auto& line : flow) fill(line, 0);

        resize_2d(capacity, new_size, new_size);
        for(auto& line : capacity) fill(line, 0);
    }
    explicit MaximumFlowProbSolver(int size) {
        init(size);
    }
    MaximumFlowProbSolver() = default;

    void reload() {
        PII person_range = {1, n + 1};
        for(int p = person_range.first; p < person_range.second; p++) {
            capacity[get_size() - 2][p] = k + 1;
        }
        capacity[0][get_size() - 2] = flow[0][get_size() - 2] + k;

        if(DEBUG) cout << flow[0][get_size() - 2] << endl;
    }

    int solve(int source, int sink) {
        while(true) {
            single_flow(source, sink);

            if(from[sink] == -1) break; // no more

            int amount = 2147483647;
            for(int iter = sink; iter != source; iter = from[iter]) {
                amount = std::min(amount, capacity[from[iter]][iter] - flow[from[iter]][iter]);
            }

            for(int iter = sink; iter != source; iter = from[iter]) {
                flow[from[iter]][iter] += amount;
                flow[iter][from[iter]] -= amount;
            }

            ret += amount;
        }

        return ret;
    }
    void print_graph_with_bfs(int start) {
        std::vector<bool> visited(size);
        for(int i = 0; i < size; i++) visited[i] = false;

        std::queue<int> container;

        container.push(start);
        visited[start] = true;

        while(not container.empty()) {
            int cnt = container.size();
            REPEAT(cnt) {
                int cur = container.front();
                container.pop();
                std::cout << cur << ' ';

                for(int next : graph[cur]) {
                    if(visited[next]) continue;
                    visited[next] = true;

                    container.push(next);
                }
            }
            std::cout << ENDL;
        }
    }
    int get_size() const {return size;}
    void input();
};

void MaximumFlowProbSolver::input() {
    cin >> n >> m >> k;

    init(n + m + 3);

    PII person_range = {1, n + 1};
    PII task_range = {n + 1, n + m + 1};
    int source = 0;
    int mid = size - 2;
    int sink = size - 1;

    connect(source, mid, n);

    for(int t = task_range.first; t < task_range.second; t++) {
        connect(t, sink, 1);
    }

    for(int p = person_range.first; p < person_range.second; p++) {
        int cnt = 0; cin >> cnt;

        REPEAT(cnt) {
            int t; cin >> t;
            int task = task_range.first + t - 1; // 1_based

            connect(p, task, 1);
        }

        connect(mid, p, 1);
    }
}


int main() {
    MaximumFlowProbSolver solver;
    solver.input();

    if(DEBUG) solver.print_graph_with_bfs(0);

    solver.solve(0, solver.get_size() - 1);
    solver.reload();
    cout << solver.solve(0, solver.get_size() -1 );
}