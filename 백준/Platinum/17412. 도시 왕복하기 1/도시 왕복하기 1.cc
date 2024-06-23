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
#define INF 2147483647



#define MAX_N 400

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
public:
    void init(int new_size) {
        this->size = new_size;

        graph.resize(new_size);
        from.resize(new_size);
        resize_2d(flow, new_size, new_size);
        resize_2d(capacity, new_size, new_size);
    }
    explicit MaximumFlowProbSolver(int size) {
        init(size);
    }

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

    void input();
};

void MaximumFlowProbSolver::input() {
    int p; std::cin >> p;
    int u, v;
    REPEAT(p) {
        std::cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);

        capacity[u][v]++;
    }
}

int main() {
    FAST_IO;

    int n; std::cin >> n;
    MaximumFlowProbSolver solver(n + 1);
    solver.input();

    std::cout << solver.solve(1, 2);
}
