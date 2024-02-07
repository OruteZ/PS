#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

#define MAX_N 10000

vector<int> graph[MAX_N + 1];

int get_count(int start_v) {
    queue<int> container;
    int answer = 0;

    bool visited[MAX_N + 1];
    for(int i = 0; i <= MAX_N; i++) visited[i] = false;

    container.push(start_v);
    visited[start_v] = true;

    while(not container.empty()) {
        int cur_v = container.front(); container.pop();
        answer++;

        for(int next_v : graph[cur_v]) {
            if(visited[next_v]) continue;
            visited[next_v] = true;
            container.push(next_v);
        }
    }

    return answer;
}



int main() {
    FAST_IO

    int n, m;
    cin >> n >> m;

    while(m--) {
        int u,v; cin >> u >> v;

        graph[v].push_back(u);
    }

    vector<int> results(n);

    for(int i = 0; i < n; i++) {
        results[i] = get_count(i + 1);
    }

    int max_val = (*max_element(results.begin(), results.end()));

    for(int i = 0; i < n; i++) {
        if(results[i] == max_val) cout << i + 1 << ' ';
    }
}
