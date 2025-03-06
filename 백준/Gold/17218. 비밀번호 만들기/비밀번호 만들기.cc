#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);

	int n = s1.size(), m = s2.size();
	// dp[i][j] : s1의 처음 i문자와 s2의 처음 j문자에서의 LCS 길이
	vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

	// DP 테이블 채우기
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (s1[i-1] == s2[j-1])
				dp[i][j] = dp[i-1][j-1] + 1;
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}

	// dp 테이블을 바탕으로 LCS 역추적 (문제 조건에 따라 LCS는 유일함)
	int i = n, j = m;
	string lcs = "";
	while (i > 0 && j > 0) {
		if (s1[i-1] == s2[j-1]) {
			lcs.push_back(s1[i-1]);
			i--;
			j--;
		} else {
			if (dp[i-1][j] >= dp[i][j-1])
				i--;
			else
				j--;
		}
	}
	reverse(lcs.begin(), lcs.end());

	cout << lcs;

	return 0;
}
