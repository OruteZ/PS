#include<bits/stdc++.h>
#define INF 1e9
#define PII std::pair<int, int>
#define DEBUG false

using namespace std;

// 방향 벡터 (상하좌우)
int DI[] = { -1, 1, 0, 0};
int DJ[] = { 0, 0, -1, 1};

// 맵 크기와 맵 정보
int N, M;
vector<vector<char>> Grid;
vector<PII> Vertices;

// BFS를 사용하여 두 정점 간의 최단 거리를 계산하는 함수
int bfs(PII start, PII end) {
	vector<vector<int>> dist(N, vector<int>(N, INF));
	queue<PII> q;
	q.push(start);
	dist[start.first][start.second] = 0;

	while (!q.empty()) {
		PII p = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int ni = p.first + DI[i];
			int nj = p.second + DJ[i];

			if(ni == end.first && nj == end.second) {
				return dist[p.first][p.second] + 1;
			}

			if (ni >= 0 && ni < N && nj >= 0 && nj < N && Grid[ni][nj] != '1' && dist[ni][nj] == INF) {
				dist[ni][nj] = dist[p.first][p.second] + 1;
				q.emplace(ni, nj);
			}
		}
	}

	return dist[end.first][end.second];
}

// Kruskal 알고리즘을 사용하여 MST를 구하는 함수
int findParent(vector<int>& parent, int x) {
	if (parent[x] == x) return x;
	return parent[x] = findParent(parent, parent[x]);
}

void unionSets(vector<int>& parent, int a, int b) {
	a = findParent(parent, a);
	b = findParent(parent, b);
	if (a < b) parent[b] = a;
	else parent[a] = b;
}

int kruskalMST(vector<tuple<int, int, int>>& edges, size_t pointCount) {
	sort(edges.begin(), edges.end());

	vector<int> parent(pointCount);
	for (int i = 0; i < pointCount; i++) parent[i] = i;

	int totalWeight = 0;
	int edgeCount = 0;

	for (auto [weight, u, v] : edges) {
		if (findParent(parent, u) != findParent(parent, v)) {
			unionSets(parent, u, v);
			totalWeight += weight;
			edgeCount++;
			if (edgeCount == pointCount - 1) break;
		}
	}

	return (edgeCount == pointCount - 1) ? totalWeight : -1;  // -1은 모든 정점을 연결할 수 없는 경우
}

int main() {
	cin >> N >> M;
	Grid.resize(N, vector<char>(N));

	// 맵 입력 받기
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> Grid[i][j];
			if (Grid[i][j] == 'S' || Grid[i][j] == 'K') {
				Vertices.emplace_back(i, j);
			}
		}
	}

	if(DEBUG) {
		cout << "Vertices: " << endl;
		for(auto& v : Vertices) {
			cout << v.first << " " << v.second << endl;
		}
		cout << endl;
	}

	// 정점 수와 간선 리스트 생성
	size_t pointCount = Vertices.size();
	vector<tuple<int, int, int>> edges;

	// 모든 정점 쌍 간의 거리를 계산하여 간선 리스트에 추가
	for (int i = 0; i < pointCount; i++) {
		for (int j = i + 1; j < pointCount; j++) {
			int distance = bfs(Vertices[i], Vertices[j]);

			if(DEBUG) {
				cout << "Distance between " << i << " and " << j << ": " << distance << endl;
			}

			if (distance != INF) {
				edges.emplace_back(distance, i, j);
			}
		}
	}

	int mstCost = kruskalMST(edges, pointCount);
	cout << mstCost << endl;

	return 0;
}
