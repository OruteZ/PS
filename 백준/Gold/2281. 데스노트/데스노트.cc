#include <bits/stdc++.h>
using namespace std;

static const long long INF = LLONG_MAX;

int n, m;
vector<long long> lengthArr;
vector<long long> memo; // 메모이제이션 배열

// i번째 이름을 "새 줄의 시작"으로 두었을 때
// i번째부터 n-1번째 이름까지 배치해 얻을 수 있는
// 남은 칸 제곱합(마지막 줄 제외)의 최소값을 반환
long long solve(int i) {
	if (i == n) return 0;
	if (memo[i] != -1) return memo[i];

	long long ret = INF;
	long long currentLen = 0; // i부터 j까지 이름 길이 합

	// i번째부터 j번째 이름까지 한 줄에 담을 수 있는지 시도
	for (int j = i; j < n; j++) {
		// 현재 줄에 (j-i)개의 공백 + (j-i+1)개 이름 길이를 더함
		currentLen += lengthArr[j];

		// 남은 칸 leftover = m - (이름 길이 합 + 공백 수)
		long long leftover = m - (currentLen + (j - i));

		// leftover가 음수가 되면 한 줄에 더 담을 수 없으므로 중단
		if (leftover < 0) break;

		// 만약 j가 마지막 이름(n-1)이라면 => 마지막 줄이므로 공백 비용 0
		long long cost = 0;
		if (j < n - 1) {
			cost = leftover * leftover;
		}

		// 이어서 (j+1)번째 이름부터의 최소 비용을 더함
		long long candidate = cost + solve(j + 1);
		ret = min(ret, candidate);
	}

	memo[i] = ret;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	lengthArr.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> lengthArr[i];
	}

	memo.assign(n, -1);
	cout << solve(0) << "\n";
	return 0;
}
