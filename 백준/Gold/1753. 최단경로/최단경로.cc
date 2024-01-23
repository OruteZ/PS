#include<iostream>
#include<queue>
#include<vector>

#define INF (1'000'000)
#define MAX_N (20'000)
#define MAX_E (300'000)

using namespace std;

class DistData {
public:
    int distance;
    int point;

    DistData(int point, int distance) {
        this->distance = distance;
        this->point = point;
    }
};
struct compare {
    bool operator() (DistData &left, DistData &right) {
        return left.distance > right.distance;
    }
};

vector<DistData> graph[MAX_N + 1];
int N, M;

void init_graph() {
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }
}

vector<int> dijkstra(int start) {
    vector<int> dist(N + 1);
    for(int &i : dist) i = INF;
    dist[start] = 0;

    priority_queue<DistData, vector<DistData>, compare> container;
    container.emplace(start, 0);

    while(not container.empty()) {
        DistData cur_data = container.top();
        int cur_point = cur_data.point;
        int cur_dist = cur_data.distance;
        container.pop();

        if(cur_dist > dist[cur_point]) continue;

        for(auto &next : graph[cur_point]) {
            //본인으로 가는 길은 의미 없으니 패스
            if(next.point == cur_point) continue;
            //cur_point를 통해서 가는길보다 기존 최단경로가 더 짧으면 패스
            if(next.distance + dist[cur_point] >= dist[next.point]) continue;

            dist[next.point] = next.distance + dist[cur_point];
            container.emplace(next.point, dist[next.point]);
        }
    }

    return dist;
}

int main() {
    int start;
    cin >> N >> M >> start;
    init_graph();

    //print_graph();

    vector<int> answer = dijkstra(start);
    for(int i = 1; i <= N; i++) {
        if(answer[i] == INF)
            cout << "INF" << '\n';
        else
            cout << answer[i] << '\n';
    }
}
