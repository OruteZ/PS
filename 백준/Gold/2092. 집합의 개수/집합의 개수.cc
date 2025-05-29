#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000;

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, A, S, B;
    cin >> T >> A >> S >> B;
    vector<int> freq(T+1, 0);
    for (int i = 0, x; i < A; i++){
        cin >> x;
        freq[x]++;
    }

    vector<int> dp(A+1, 0), new_dp(A+1);
    dp[0] = 1;

    // 값 1..T 순회
    for (int v = 1; v <= T; v++){
        int f = freq[v];
        if (f == 0) continue;

        // dp의 누적합 계산
        vector<int> ps(A+1);
        ps[0] = dp[0];
        for (int i = 1; i <= A; i++){
            ps[i] = add(ps[i-1], dp[i]);
        }

        // new_dp[k] = ps[k] - ps[k-f-1] (범위 조정)
        for (int k = 0; k <= A; k++){
            int low = k - f - 1;
            if (low >= 0) new_dp[k] = sub(ps[k], ps[low]);
            else          new_dp[k] = ps[k];
        }

        dp.swap(new_dp);
    }

    // S..B 합산
    int ans = 0;
    for (int k = S; k <= B; k++){
        ans = add(ans, dp[k]);
    }
    cout << ans << "\n";
    return 0;
}
