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

int main() {
    int n; std::cin >> n;

    std::vector<int> nums(n);
    for(int& i : nums) std::cin >> i;
    std::sort(nums.begin(), nums.end());

    int result = 1;
    for(const int& num : nums) {
        if(result < num) break;
        result += num;
    }

    std::cout << result;
}

//---------------------------------------------------------

#pragma clang diagnostic pop