#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int, int>> positions;
vector<vector<ll>> dp;


int dist(int idx1, int idx2) {
	return abs(positions[idx1].first - positions[idx2].first) + abs(positions[idx1].second - positions[idx2].second);
}

// 각 경찰차들이 마지막으로 위치했던 곳
ll findMinDistSum(int police1, int police2) {
	int next = max(police1, police2) + 1;
	if (next == positions.size()) return 0;

	if (dp[police1][police2] != -1) return dp[police1][police2];

	ll nextDist = dist(police1, next) + findMinDistSum(next, police2);
	ll nextDist2 = dist(police2, next) + findMinDistSum(police1, next);

	return dp[police1][police2] = min(nextDist, nextDist2);
}

// dp에 저장된 값에 기반하여, 어떤 경찰차가 갔는지 로그를 추적합니다.
void trackLog(int police1, int police2) {
	int next = max(police1, police2) + 1;
	if (next == positions.size()) return;

	ll nextDist = dist(police1, next) + findMinDistSum(next, police2);
	ll nextDist2 = dist(police2, next) + findMinDistSum(police1, next);

	if (nextDist < nextDist2) {
		cout << 1 << endl;
		trackLog(next, police2);
	} else {
		cout << 2 << endl;
		trackLog(police1, next);
	}

}

int main() {
	int n; cin >> n;
	int pos_size; cin >> pos_size;

	positions.resize(pos_size + 2);
	dp.resize(pos_size + 2, vector<ll>(pos_size + 2, -1));

	positions[0] = {1, 1};
	positions[1] = {n, n};
	for (int i = 2; i < pos_size + 2; i++) {
		cin >> positions[i].first >> positions[i].second;
	}

	cout << findMinDistSum(0, 1) << endl;
	trackLog(0, 1);
}