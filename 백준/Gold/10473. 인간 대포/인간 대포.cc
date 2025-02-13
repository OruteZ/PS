#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>

using namespace std;

double getDist(const pair<double, double>& a, const pair<double, double>& b) {
    double first_diff = (a.first - b.first) * (a.first - b.first);
    double second_diff = (a.second - b.second) * (a.second - b.second);
    return sqrt(first_diff + second_diff);
}

struct Edge {
    int to;
    double weight;
};

double calculateWeight(double dist) {
    double cannon_time = abs(dist - 50.0) / 5.0 + 2;
    double walk_time = dist / 5.0;

    return min(cannon_time, walk_time);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    pair<double, double> start, dest;
    cin >> start.first >> start.second;
    cin >> dest.first >> dest.second;

    int n;
    cin >> n;

    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    // 그래프 구성
    vector<vector<Edge>> graph(n + 2);  // 시작점 + 목적지 + 중간점들

    // 시작점과 목적지를 포함한 간선 추가

    // 시작점 -> 각 대포
    for (int i = 0; i < n; i++) {
        double dist = getDist(start, points[i]);
        graph[0].push_back({ i + 1, dist / 5.0 });
    }
    // 시작점 -> 목적지 그냥 걷기
    graph[0].push_back({ n + 1, getDist(start, dest) / 5.0 });

    // 대포 사이 간선 추가
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = getDist(points[i], points[j]);
            double weight = calculateWeight(dist);
            graph[i + 1].push_back({ j + 1, weight });
            graph[j + 1].push_back({ i + 1, weight });
        }
    }

    // 대포 -> 목적지
    for (int i = 0; i < n; i++) {
        double dist = getDist(points[i], dest);

        graph[i + 1].push_back({ n + 1, calculateWeight(dist) });
    }

    // 다익스트라 알고리즘
    vector<double> dist(n + 2, numeric_limits<double>::infinity());
    dist[0] = 0.0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({ 0.0, 0 });

    while (not pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            double weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }

    // 결과 출력
    cout << dist[n + 1] << "\n";

    return 0;
}
