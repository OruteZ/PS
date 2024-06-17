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

//--------------------------------------------------

int main() {
    long long int a, b;
    std::cin >> a >> b;

    if(a > b) {
        int temp = a;
        a =b;
        b = temp;
    }

    std::cout << std::abs(b - a + 1) * (a + b) / 2;

}