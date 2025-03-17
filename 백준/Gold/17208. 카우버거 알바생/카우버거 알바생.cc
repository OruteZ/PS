#include<bits/stdc++.h>

using namespace std;

int main() {
    // fast io
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int order_cnt;
    int max_c;
    int max_p;

    vector<pair<int, int>> orders;

    cin >> order_cnt >> max_c >> max_p;
    for (int i = 0; i < order_cnt; i++) {
        int c, p;
        cin >> c >> p;
        orders.emplace_back(c, p);
    }

    // 3차원 knapsack
    // dp[i][c][p] = i번째 주문까지 고려했을 때, c원 이하로 구매하고 p원 이하로 지불할 수 있는 최대 주문 수
    vector<vector<vector<int>>> dp
        (order_cnt + 1, vector<vector<int>>(max_c + 1, vector<int>(max_p + 1, 0)));
    
    for (int i = 1; i <= order_cnt; i++) {
        for (int c = 0; c <= max_c; c++) {
            for (int p = 0; p <= max_p; p++) {
                dp[i][c][p] = dp[i - 1][c][p];
                if (c >= orders[i - 1].first && p >= orders[i - 1].second) {
                    dp[i][c][p] = max(dp[i][c][p], dp[i - 1][c - orders[i - 1].first][p - orders[i - 1].second] + 1);
                }
            }
        }
    }

    cout << dp[order_cnt][max_c][max_p] << '\n';

}

