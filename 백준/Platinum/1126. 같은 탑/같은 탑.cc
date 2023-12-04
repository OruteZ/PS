#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<set>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX_H 500'000
#define MAX_N 50

int height[MAX_N];

int memo[MAX_N][MAX_H + 1];

void clear() {
    for(auto &i : memo) {
        for(auto &j : i) {
            j = -1;
        }
    }

    memo[0][0] = 0;
}

int dp(int i, int h_diff) {

    //memoization
    if(memo[i][h_diff] != -1) {
        return memo[i][h_diff];
    }

    //exception
//    if(h_diff > MAX_H / 2) return -MAX_H;

    //base case : i == 0
    if(i == 0) {
        if(h_diff == 0) return 0;
        else if(h_diff == height[0]) return height[0];
        else return -MAX_H;
    }

    std::set<int> h_set;

    //case 1 : i번째 블럭 미포함
    h_set.insert(dp(i - 1, h_diff));

    //case 2 : 더 낮은 쪽에 쌓여서 변하지 않을 때
    h_set.insert(dp(i - 1, h_diff + height[i]));

    //case 3 - 1 : height[i] <= h_diff
    if(height[i] <= h_diff)
        h_set.insert(dp(i - 1, h_diff - height[i]) + height[i]);

    //case 3 - 2 : height[i] > h_diff;
    else
        h_set.insert(dp(i - 1, height[i] - h_diff) + h_diff);

    return memo[i][h_diff] = *h_set.rbegin();
}

int main() {
    FAST_IO;

    clear();

    int n; std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> height[i];
    }

    int ret = dp(n - 1, 0);
    std::cout << (ret <= 0 ? -1 : ret) << std::endl;
}