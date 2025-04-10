#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    string current, target;
    cin >> current >> target;
    
    // 각 숫자를 정수로 변환하여 벡터에 저장
    vector<int> curr(N), targ(N);
    for (int i = 0; i < N; i++){
        curr[i] = current[i] - '0';
        targ[i] = target[i] - '0';
    }
    
    const int INF = 1e9;
    // dp[i][offset] : i번째 나사부터 목표 상태로 만들기 위한 최소 회전 칸수 (offset은 0~9)
    vector<vector<int>> dp(N + 1, vector<int>(10, INF));
    
    for (int off = 0; off < 10; off++){
        dp[N][off] = 0;
    }
    
    // 나사 번호 (N-1)부터 0까지 역순으로 DP 계산
    for (int i = N - 1; i >= 0; i--){
        for (int off = 0; off < 10; off++){
            int current_value = (curr[i] + off) % 10;
            int L = (targ[i] - current_value + 10) % 10;
            int R = (10 - L) % 10;
            
            int cost_left = L + dp[i + 1][(off + L) % 10];
            int cost_right = R + dp[i + 1][off];
            
            dp[i][off] = min(cost_left, cost_right);
        }
    }
    
    // 초기 오프셋 0에서 시작
    cout << dp[0][0] << "\n";
    
    return 0;
}
