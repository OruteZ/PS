#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    sort(a.begin(), a.end());

    vector<int> dp(N, 1);
    int best = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] % a[j] == 0) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        best = max(best, dp[i]);
    }

    cout << (N - best) << "\n";
    return 0;
}