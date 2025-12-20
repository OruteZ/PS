#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> best(N + 1, vector<int>(N + 1, 0));
    for (int i = 0; i < K; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a >= b) continue;               // 번호 증가만 허용
        best[a][b] = max(best[a][b], c);    // 같은 (a,b) 중 최대만
    }

    const int NEG = -1;
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, NEG));
    dp[1][1] = 0;

    for (int cnt = 2; cnt <= M; cnt++) {
        for (int v = 2; v <= N; v++) {
            int bestVal = NEG;
            for (int u = 1; u < v; u++) {
                if (best[u][v] == 0) continue;
                if (dp[cnt - 1][u] == NEG) continue;
                bestVal = max(bestVal, dp[cnt - 1][u] + best[u][v]);
            }
            dp[cnt][v] = bestVal;
        }
    }

    int ans = 0;
    for (int cnt = 2; cnt <= M; cnt++) ans = max(ans, dp[cnt][N]);
    cout << ans << "\n";
    return 0;
}
