#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;

inline int add(int a, int b) {
    int res = a + b;
    return (res >= MOD ? res - MOD : res);
}

inline int sub(int a, int b) {
    int res = a - b;
    return (res < 0 ? res + MOD : res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C;
    cin >> N >> C;

    // dp[j] = DP[i-1][j], newDp[j] = DP[i][j]
    vector<int> dp(C + 1, 0), newDp(C + 1, 0), pre(C + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= N; ++i) {
        // 1) 이전 dp의 prefix-sum 계산
        pre[0] = dp[0];
        for (int j = 1; j <= C; ++j) {
            pre[j] = add(pre[j - 1], dp[j]);
        }
        // 2) 새로운 dp값 계산
        for (int j = 0; j <= C; ++j) {
            int left = j - i;
            if (left >= 0) {
                // pre[j] - pre[j-i]
                newDp[j] = sub(pre[j], pre[left]);
            } else {
                // j < i 이면 전부 더한 값
                newDp[j] = pre[j];
            }
        }
        // 3) dp 교체
        dp.swap(newDp);
    }

    // 답: 길이 N, 혼란도 C인 순열의 개수
    cout << dp[C] << '\n';
    return 0;
}
