#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int INF = 1e9;

// (n, k) 상태를 관리하기 위한 dp: dp[n][k] = 최소 작업 횟수
vector<unordered_map<int, int>> dp;

int solve(int n, int k, const vector<int>& stones) {
	if(k < 0) return INF;

	// base case: 마지막 장소일 때
	if(n == stones.size() - 1)
		return (k > 0) ? 1 : 0;

	// dp 캐시 사용: dp[n][k]
	if(dp[n].count(k)) return dp[n][k];

	// 두 가지 경우를 고려
	// 1. 인접하지 않은 작업: n번 자리에 남은 조약돌 k를 0으로 만든 후, 다음 장소에서 stones[n+1]만큼의 조약돌이 남은 상태로 진행
	int case1 = solve(n + 1, stones[n + 1], stones) + 1;

	// 2. 인접한 두 장소 작업: n+1번 자리의 조약돌 개수를 k만큼 빼서 진행
	int case2 = solve(n + 1, stones[n + 1] - k, stones) + 1;

	return dp[n][k] = min(case1, case2);
}

int main(){
	int n;
	cin >> n;
	vector<int> stones(n);
	for (int i = 0; i < n; i++){
		cin >> stones[i];
	}

	// dp 크기 초기화: 각 장소마다 해시맵 사용
	dp.resize(n);

	cout << solve(0, stones[0], stones) << endl;
	return 0;
}
