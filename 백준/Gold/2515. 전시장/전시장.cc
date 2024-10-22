#include <bits/stdc++.h>

using namespace std;

int getMaxPrice(int sellable, vector<pair<int,int>>& items) {
	sort(items.begin(), items.end());

	// dp[0][i] = i번째 아이템을 전시하지 않았을 때 최대 가격
	// 전시하지 않을 수 있나? ==> 제일 큰 그림 뒤로 보내버리면 됨
	vector dp(3, vector(items.size(), 0));

	dp[1][0] = items[0].first >= sellable ? 0 : items[0].second;
	for(int i = 1; i < items.size(); i++) {
		dp[0][i] = max(dp[0][i - 1], dp[1][i - 1]);

		// 가장 높은놈이 target_h보다 높으면 전시해도 의미가 없음. 이 길이보다 작은 최대값을 찾아야 함
		int target_h = items[i].first - sellable;
		auto highest = lower_bound(items.begin(), items.end(), make_pair(target_h+1, -1)) - 1;
		int highest_idx = highest - items.begin();

		dp[2][i] = highest_idx;

		dp[1][i] = max(max(dp[0][highest_idx], dp[1][highest_idx]) + items[i].second, dp[1][i - 1]);
	}

#ifdef DEBUG
	for(int i = 0; i < items.size(); i++) {
		cout.width(3);
		cout << items[i].first << " ";
	}
	cout << endl;
	for(int i = 0; i < items.size(); i++) {
		cout.width(3);
		cout << items[i].second << " ";
	}
	cout << endl;
	cout << endl;

	for(int i = 0; i < items.size(); i++) {
		cout.width(3);
		cout << dp[0][i] << " ";
	}
	cout << endl;
	for(int i = 0; i < items.size(); i++) {
		cout.width(3);
		cout << dp[1][i] << " ";
	}
	cout << endl;
	for(int i = 0; i < items.size(); i++) {
		cout.width(3);
		cout << dp[2][i] << " ";
	}
	cout << endl;
#endif

	return max(dp[0].back(), dp[1].back());
}

int main() {
	int N, sellable;
	cin >> N >> sellable;

	vector<pair<int, int>> h_and_p(N + 1);

	h_and_p[0] = {0, 0};
	for(int i = 1; i <= N; i++) {
		cin >> h_and_p[i].first >> h_and_p[i].second;
	}

	cout << getMaxPrice(sellable, h_and_p) << endl;
}