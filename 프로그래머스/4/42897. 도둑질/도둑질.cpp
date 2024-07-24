#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int rob_linear(const vector<int>& houses) {
    int n = houses.size();
    if (n == 1) return houses[0];
    
    vector<int> dp(n, 0);
    dp[0] = houses[0];
    dp[1] = max(houses[0], houses[1]);
    
    for (int i = 2; i < n; ++i) {
        dp[i] = max(dp[i-1], dp[i-2] + houses[i]);
    }
    
    return dp[n-1];
}

int solution(vector<int> money) {
    int n = money.size();
    if (n == 1) return money[0];
    if (n == 2) return max(money[0], money[1]);
    if (n == 3) return max({money[0], money[1], money[2]});
    
    // Case 1: Rob from first house to second to last house
    vector<int> money1(money.begin(), money.end() - 1);
    int case1 = rob_linear(money1);
    
    // Case 2: Rob from second house to last house
    vector<int> money2(money.begin() + 1, money.end());
    int case2 = rob_linear(money2);
    
    return max(case1, case2);
}
