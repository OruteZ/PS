#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<set>
#include<bitset>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX 14
#define MOD(n) (n % 9901)

LL cache[MAX * MAX][1 << (MAX + 1)];
int n, m;

LL dp(int num, std::bitset<MAX + 1> state) {
    if(num == n * m and state.none()) return 1;
    if(num == n * m and state.any()) return 0;
    if(num >= n * m) return 0;

    LL &ret = cache[num][state.to_ulong()];
    if(ret != -1) return ret;

    ret = 0;

    // case 0 : 이미 자리 찼을 때
    if(state.test(0)) {
        ret = dp(num + 1, state >> 1);
        return MOD(ret);
    }

    // case 1 : 오른쪽으로 갈 수 있을 때
    // 조건 1 : 오른쪽 칸이 비어있어야 함
    // 조건 2 : 오른쪽 끝 칸이 아니어야 함
    if(!state.test(1) && (num % m != m - 1)) {
        ret += dp(num + 2, state >> 2);
    }

    // case 2 : 아래로 놓을 때 (언제든 가능)
    state.set(m, true);
    ret += dp(num + 1, state >> 1);

    return MOD(ret);
}

int main() {
    FAST_IO;

    std::cin >> n >> m;

    for(auto &a : cache) for(auto &num : a) num = -1;
    std::cout << dp(0, 0) << '\n';
}