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
#define DEBUG true
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

    int solve(int source, int sink) {
        int ret = 0;
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
    int n, m; cin >> n >> m;

    size = n + m + 2;
    init(size);

    int source = 0;
    int sink = size - 1;

    for(int i = 1; i <= n; i++) {
        graph[i].push_back(sink);
        cin >> capacity[i][sink];
    }

    for(int i = n + 1; i <= n + m; i++) {
        graph[source].push_back(i);
        cin >> capacity[source][i];
    }

    for(int j = n + 1; j <= n + m; j++) {
        for(int i = 1; i <= n; i++) {
            int p_num = i;
            int store_num = j;

            graph[p_num].push_back(store_num);
            graph[store_num].push_back(p_num);

            cin >> capacity[store_num][p_num];
        }
    }
}


int main() {
    MaximumFlowProbSolver solver;
    solver.input();

    cout << solver.solve(0, solver.get_size() - 1);
}