#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<bool> dp(N+1, false);

    if (N >= 1) dp[1] = false; 
    if (N >= 2) dp[2] = true;
    if (N >= 3) dp[3] = false;
    if (N >= 4) dp[4] = true;

    for (int i = 5; i <= N; i++) {
        if (!dp[i-1] || !dp[i-3] || !dp[i-4]) dp[i] = true;
        else dp[i] = false;
    }

    cout << (dp[N] ? "SK\n" : "CY\n");

    return 0;
}
