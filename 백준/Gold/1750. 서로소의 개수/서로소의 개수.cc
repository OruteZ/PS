#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000003;

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> a(N);
    int maxA = 0;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        maxA = max(maxA, a[i]);
    }

    // dp[g] = gcd가 g인 부분집합의 개수
    vector<int> dp(maxA + 1, 0);

    for (int x : a) {
        vector<int> new_dp = dp;  // x를 선택하지 않는 경우
        for (int g = 1; g <= maxA; ++g) {
            if (dp[g] == 0) continue;
            int ng = gcd(g, x); // x를 추가했을 때의 새로운 gcd
            int val = new_dp[ng] + dp[g];
            if (val >= MOD) val -= MOD; 
            new_dp[ng] = val;
        }

        // x 혼자 선택하는 부분집합 {x}
        int val = new_dp[x] + 1;
        if (val >= MOD) val -= MOD;
        new_dp[x] = val;

        dp.swap(new_dp);
    }

    cout << dp[1] % MOD << '\n';
    return 0;
}
