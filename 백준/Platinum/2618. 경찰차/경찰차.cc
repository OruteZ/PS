#include <bits/stdc++.h>

using namespace std;

// 모든 사건현장의 위치를 저장. 단 0번째와 1번쨰는 두 경찰차의 시작위치를 삽입
vector<pair<int, int>> positions;
vector<vector<int>> dp;

// positions[idx1]과 positions[idx2] 사이의 거리를 반환합니다.
int dist(int idx1, int idx2) {
	return abs(positions[idx1].first - positions[idx2].first) + abs(positions[idx1].second - positions[idx2].second);
}

// 각 경찰차들이 마지막으로 위치했던 곳
int findMinDistSum(int police1, int police2) {
	int next = max(police1, police2) + 1;
	if (next == positions.size()) return 0;

	if (dp[police1][police2] != -1) return dp[police1][police2];

	// 점화식 핵심 : 두 경찰차가 각각 다음 사건으로 이동했을때 결과값을 가져와서 최소값으로 변경
	int nextDist = dist(police1, next) + findMinDistSum(next, police2);
	int nextDist2 = dist(police2, next) + findMinDistSum(police1, next);

	return dp[police1][police2] = min(nextDist, nextDist2);
}

// dp에 저장된 값에 기반하여, 어떤 경찰차가 갔는지 로그를 추적합니다.
void trackLog(int police1, int police2) {
	int next = max(police1, police2) + 1;
	if (next == positions.size()) return;

	int nextDist = dist(police1, next) + findMinDistSum(next, police2);
	int nextDist2 = dist(police2, next) + findMinDistSum(police1, next);

	// police1이 이동했을 때의 거리가 더 작다면 police1이 이동했다고 출력하고, police1이 이동한 경로를 출력합니다.
	if (nextDist < nextDist2) {
		cout << 1 << endl;
		trackLog(next, police2);

	// police2가 이동했을 때의 거리가 더 작다면 police2가 이동했다고 출력하고, police2가 이동한 경로를 출력합니다.
	} else {
		cout << 2 << endl;
		trackLog(police1, next);
	}

}

int main() {
	int n; cin >> n;
	int pos_size; cin >> pos_size;

	positions.resize(pos_size + 2);
	dp.resize(pos_size + 2, vector<int>(pos_size + 2, -1));

	positions[0] = {1, 1};
	positions[1] = {n, n};
	for (int i = 2; i < pos_size + 2; i++) {
		cin >> positions[i].first >> positions[i].second;
	}

	cout << findMinDistSum(0, 1) << endl;
	trackLog(0, 1);
}