#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

//--------------------------------------------------
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)
//====

int n_digit(int num, int d) {
    int ret = 0;

    while(num > 0) {
        ret += num % d;
        num /= d;
    }

//    std::cout << d << ' ' << ret << std::endl;

    return ret;
}

int main() {
    int N; std::cin >> N;

    std::pair<int, int> answer = std::make_pair(-1, -1); // sum, digit

    int max_sum = INT_M_INF;
    for(int d = 2; d <= N; d++) {
        int result = n_digit(N, d);

        if(max_sum >= result) continue;
        max_sum = result;

        answer = std::make_pair(result, d);
    }

    std::cout << answer.first << ' ' << answer.second << std::endl;
}

//---------------------------------------------------------

#pragma clang diagnostic pop