#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1'000'000'007;

// a^b % MOD를 O(log b)에 계산
ll mod_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    ll cnt = 0;
    // 4방향 델타
    constexpr int di[4] = {1, -1, 0, 0};
    constexpr int dj[4] = {0, 0, 1, -1};

    // 각 칸에 대해 상하좌우 모두 같은 색인지 검사
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            bool flippable = true;
            for (int k = 0; k < 4; k++) {
                int ni = i + di[k], nj = j + dj[k];
                if (ni < 0 || ni >= N || nj < 0 || nj >= M) 
                    continue;
                if (grid[ni][nj] != grid[i][j]) {
                    flippable = false;
                    break;
                }
            }
            if (flippable) cnt++;
        }
    }

    // 답은 2^cnt % MOD
    cout << mod_pow(2, cnt) << "\n";
    return 0;
}
