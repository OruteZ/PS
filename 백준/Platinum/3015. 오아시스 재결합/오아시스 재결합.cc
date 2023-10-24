#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include <stack>

#pragma region MACRO

#define LL long long
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)

#pragma endregion

#define MAX 500'000

void solve() {
    LL answer = 0;
    int size; std::cin >> size;

    std::stack<std::pair<int, int>> stk;
    int p;

    for(int i = 0; i < size; i++) {
        std::cin >> p;

        while(not stk.empty()) {
            if(stk.top().first >= p) break;

            answer += stk.top().second;
            stk.pop();
        }

        if(stk.empty()) {
            stk.emplace(p, 1);
            continue;
        }

        if(DEBUG) std::cout << p << " " << stk.top().first << ":" << stk.top().second << ' ';

        if(p < stk.top().first) stk.emplace(p, 1);
        else stk.top().second++;

        answer += stk.top().second;
        answer = stk.size() == 1 ? answer - 1 : answer;

        if(DEBUG) std::cout << answer << '\n';
    }

    std::cout << answer << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    solve();


    return 0;
}