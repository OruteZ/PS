#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> cuts(M);
    for(int i = 0; i < M; i++){
        cin >> cuts[i];
    }
    sort(cuts.begin(), cuts.end());

    // 잘라야 할 위치 배열 pos: [0, cuts..., N]
    int K = M + 2;
    vector<int> pos(K);
    pos[0] = 0;
    for(int i = 1; i <= M; i++){
        pos[i] = cuts[i-1];
    }
    pos[M+1] = N;

    // dp[i][j]: pos[i]~pos[j] 구간을 모두 자르는 최소 비용
    // opt[i][j]: dp[i][j]를 최적화시킨 k의 위치
    vector<vector<ll>> dp(K, vector<ll>(K, 0));
    vector<vector<int>> opt(K, vector<int>(K, 0));

    // 길이가 1인 구간(이웃한 i, i+1)은 비용 0, opt는 i+1
    for(int i = 0; i+1 < K; i++){
        dp[i][i+1] = 0;
        opt[i][i+1] = i+1;
    }

    // 구간 길이 len = 2 부터 K-1 까지
    for(int len = 2; len < K; len++){
        for(int i = 0; i + len < K; i++){
            int j = i + len;
            ll bestCost = LLONG_MAX;
            int bestK = -1;

            // Knuth 최적화: k ∈ [opt[i][j-1], opt[i+1][j]] ∩ [i+1, j-1]
            int start = max(opt[i][j-1],   i+1);
            int end   = min(opt[i+1][j], j-1);
            for(int k = start; k <= end; k++){
                ll cost = dp[i][k] + dp[k][j] + (pos[j] - pos[i]);
                if(cost < bestCost){
                    bestCost = cost;
                    bestK = k;
                }
            }

            dp[i][j]  = bestCost;
            opt[i][j] = bestK;
        }
    }

    // 전체 구간 [0, K-1] 의 답
    cout << dp[0][K-1] << "\n";
    return 0;
}
