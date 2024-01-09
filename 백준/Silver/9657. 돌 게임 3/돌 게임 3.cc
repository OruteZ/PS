#include<iostream>

#define MAX 1000

int is_winning_turn(int n) {
    bool dp[MAX + 1];
    dp[1] = true;
    dp[2] = false;
    dp[3] = true;
    dp[4] = true;

    for(int i = 5; i <= n; i++) {
        if(dp[i - 1] and dp[i - 3] and dp[i - 4]) dp[i] = false;
        else dp[i] = true;
    }

    return dp[n];
}

int main() {
    int n;
    std::cin >> n;
    if(is_winning_turn(n)) {
        std::cout << "SK";
    }
    else {
        std::cout << "CY";
    }
}
