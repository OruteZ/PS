#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <cassert>

using namespace std;
using ll = long long;

struct Edge {
	int u, v;
	int cat; // 0: A, 1: B, 2: C, 3: D, 4: E
};

struct DSU {
	vector<int> parent;
	vector<int> rank;
	DSU(int n) : parent(n+1), rank(n+1, 0) {
		for (int i = 0; i <= n; i++)
			parent[i] = i;
	}
	int find(int a) {
		if (parent[a] == a) return a;
		return parent[a] = find(parent[a]);
	}
	bool unionSets(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (rank[a] < rank[b])
			swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			rank[a]++;
		return true;
	}
};

// 해시 함수: std::array<int,5>를 키로 사용하기 위한 해시
struct ArrayHash {
	size_t operator()(const array<int, 5>& arr) const {
		size_t h = 0;
		for (int x : arr) {
			h = h * 31u + std::hash<int>()(x);
		}
		return h;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, Q;
	cin >> N >> M >> Q;
	vector<Edge> edges(M);
	// 문자 A, B, C, D, E 를 0,1,2,3,4 로 맵핑
	for (int i = 0; i < M; i++) {
		int u, v;
		char ch;
		cin >> u >> v >> ch;
		int cat = ch - 'A'; // 'A'->0, 'B'->1, ...
		edges[i] = {u, v, cat};
	}

	// 모든 5개 대학(카테고리)의 순열 (총 120가지)를 생성
	vector<array<int, 5>> perms;
	array<int, 5> base = {0,1,2,3,4};
	do {
		perms.push_back(base);
	} while(next_permutation(base.begin(), base.end()));

	// 각 순열에 대해, MST 구성 시 각 대학별 선택된 도로의 개수(count vector)를 계산
	unordered_map<array<int, 5>, array<int, 5>, ArrayHash> permToCounts;
	for (auto &perm : perms) {
		// rank[cat] = 우선순위 (낮을수록 먼저 고려)
		array<int, 5> rank{};
		for (int pos = 0; pos < 5; pos++){
			rank[ perm[pos] ] = pos;
		}
		// edges를 복사하여 정렬: 각 도로의 "가중치"는 rank[edge.cat]
		vector<Edge> sortedEdges = edges;
		sort(sortedEdges.begin(), sortedEdges.end(), [&](const Edge &a, const Edge &b){
		  return rank[a.cat] < rank[b.cat];
		});
		DSU dsu(N);
		array<int, 5> counts = {0, 0, 0, 0, 0};
		int cnt = 0;
		// MST 구성 (N-1개의 간선을 선택하면 종료)
		for (auto &e : sortedEdges) {
			if (dsu.unionSets(e.u, e.v)) {
				counts[e.cat]++;
				cnt++;
				if (cnt == N - 1) break;
			}
		}
		// MST가 완성되었는지 확인 (연결 그래프이므로 항상 N-1개 선택될 것임)
		assert(cnt == N - 1);
		permToCounts[perm] = counts;
	}

	// 쿼리 처리: 각 쿼리마다 비용 벡터 (a, b, c, d, e)에 따라 우선순위 결정 후 MST 비용 계산
	for (int qi = 0; qi < Q; qi++){
		array<ll, 5> cost{};
		for (int i = 0; i < 5; i++){
			cin >> cost[i];
		}
		// 비용 벡터와 대학 번호를 pair로 저장하고 정렬
		vector<pair<ll, int>> pr;
		for (int i = 0; i < 5; i++){
			pr.emplace_back(cost[i], i);
		}
		// tie-break: 비용이 같으면 낮은 대학 번호(A=0, B=1,...)가 먼저
		sort(pr.begin(), pr.end(), [&](const pair<ll,int>& a, const pair<ll,int>& b){
		  if(a.first == b.first) return a.second < b.second;
		  return a.first < b.first;
		});
		// 현재 쿼리에 해당하는 우선순위 순열 (낮은 비용 우선)
		array<int, 5> curPerm{};
		for (int i = 0; i < 5; i++){
			curPerm[i] = pr[i].second;
		}
		// 미리 계산해둔 MST의 카운트 벡터를 불러옴
		array<int, 5> counts = permToCounts[curPerm];
		ll ans = 0;
		for (int i = 0; i < 5; i++){
			ans += cost[i] * counts[i];
		}
		cout << ans << "\n";
	}

	return 0;
}
