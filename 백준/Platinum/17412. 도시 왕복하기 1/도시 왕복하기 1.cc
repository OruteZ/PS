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

using namespace std;


#define MAX_N 400

vector<vector<int>> graph;
int flow[MAX_N + 1][MAX_N + 1];
int capacity[MAX_N + 1][MAX_N + 1];
bool visited[400] = {false,};

void print_vec(vector<int> vec) {
    PRINT_LINE;
    for(int i : vec) std::cout << i << ' ';
    std::cout << ENDL;
    PRINT_LINE;
}


int maximum_flow(int source, int sink) {
    int ret = 0;

    vector<int> from(MAX_N + 1);

    while(true) {
        for(int& i : from) i = -1;

        queue<int> container;
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

        if(from[sink] == -1) break; // no more

        int amount = INF;
        for(int iter = sink; iter != source; iter = from[iter]) {
            amount = min(amount, capacity[from[iter]][iter] - flow[from[iter]][iter]);
        }

        for(int iter = sink; iter != source; iter = from[iter]) {
            flow[from[iter]][iter] += amount;
            flow[iter][from[iter]] -= amount;
        }

        ret += amount;
    }

    return ret;
}

void resize_2D(vector<vector<int>>& vec, int size) {
    vec.resize(size);
    for(int i = 0; i < size; i++) {
        vec[i].resize(size);
    }
}



int main() {
    FAST_IO;

    int n, p;
    cin >> n >> p;

    resize_2D(graph, n + 1);

    int u,v;
    REPEAT(p) {
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);

        capacity[u][v]++;
//        capacity[v][u]++;
    }

    cout << maximum_flow(1, 2);
}
