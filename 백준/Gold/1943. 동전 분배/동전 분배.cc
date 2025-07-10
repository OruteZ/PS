#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int tc = 0; tc < 3; ++tc){
        int N;
        if(!(cin >> N)) break;  // 입력이 부족한 경우 종료

        vector<int> value(N), count(N);
        long long sum = 0;
        for(int i = 0; i < N; ++i){
            cin >> value[i] >> count[i];
            sum += 1LL * value[i] * count[i];
        }

        // 총합이 홀수이면 반으로 나눌 수 없다
        if(sum % 2 != 0){
            cout << 0 << "\n";
            continue;
        }

        int target = sum / 2;
        // dp[j]: 액수 j를 만들 수 있는지, 만들 수 있다면
        //        현재 동전 종류에서 남은 개수(>=0), 그렇지 않으면 -1
        vector<int> dp(target + 1, -1);
        dp[0] = 0;

        // 각 동전 종류마다 DP 갱신
        for(int i = 0; i < N; ++i){
            int v = value[i], c = count[i];
            // 1) 기존에 가능했던 j들은 모두 c개만큼 동전 사용 여유를 부여
            for(int j = 0; j <= target; ++j){
                if(dp[j] >= 0) dp[j] = c;
                else           dp[j] = -1;
            }
            // 2) 실제로 동전을 하나 더 써서 새로운 액수를 만든다
            for(int j = v; j <= target; ++j){
                if(dp[j] < 0 && dp[j - v] > 0){
                    dp[j] = dp[j - v] - 1;
                }
            }
        }

        // target 액수를 만들 수 있다면 1, 아니면 0
        cout << (dp[target] >= 0 ? 1 : 0) << "\n";
    }

    return 0;
}
