#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

long long dp[200];

long long solve(int n) {
    if(n <= 3) return 1;
    if(dp[n] != 0) return dp[n];

    long long& ret = dp[n];
    ret = solve(n - 1) + solve(n - 3);

    return ret;
}

int main() {
    FAST_IO

    int n; cin >> n;
    cout << solve(n);
}
