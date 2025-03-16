#include<bits/stdc++.h>

using namespace std;
typedef long long int ll;


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n + 1);
	vector<vector<int>> reverse_graph(n + 1);
	vector<int> outdeg(n + 1, 0);

	// 간선 입력 (중복 간선이 있을 수 있음에 유의)
	for (int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		reverse_graph[v].push_back(u);
		outdeg[u]++;
	}

	queue<int> q;
	vector<bool> safe(n + 1, false);

	// 출발 간선이 없는 노드(터미널 노드)는 안전
	for (int i = 1; i <= n; i++){
		if(outdeg[i] == 0){
			q.push(i);
			safe[i] = true;
		}
	}

	// 역방향 탐색: 터미널 노드부터 시작하여, 선행 노드들의 outdegree를 줄여나감
	while(not q.empty()){
		int cur = q.front();
		q.pop();
		for(auto prev : reverse_graph[cur]){
			outdeg[prev]--;
			if(outdeg[prev] == 0){
				safe[prev] = true;
				q.push(prev);
			}
		}
	}

	// 안전한 노드의 수 계산
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		if(safe[i]) cnt++;
	}

	cout << cnt << "\n";
	return 0;
}