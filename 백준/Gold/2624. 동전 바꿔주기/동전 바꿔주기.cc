#include<bits/stdc++.h>

using namespace std;

int main() {
    int target, coin_cnt;

    cin >> target >> coin_cnt;
    
    // <value, cnt>
    vector<pair<int, int>> coins(coin_cnt);


    for(int i = 0; i < coin_cnt; i++) {
        cin >> coins[i].first;
        cin >> coins[i].second;
    }

    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    // 3중 for
    // k * T * n
    // 10000 * 10000 * 100

    for(pair<int, int>& coin : coins) {
        for(int money = target; money >= 0; money--) {
            for(int cnt = 1; cnt <= coin.second; cnt++) {
                int before = money - coin.first * cnt;
                if(before < 0) break;

                dp[money] += dp[before];
            }
        }
    }

    cout << dp[target] << '\n';
}