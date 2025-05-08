#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cube = array<int, 3>;

// memoization
int dp_cut[205][205][205];

int slice_cub(const cube &c) {
    // 정육면체 처리
    if(c[0] == c[1] && c[1] == c[2]) {
        dp_cut[c[0]][c[1]][c[2]] = 0;
        return 0;
    }
    if(dp_cut[c[0]][c[1]][c[2]] != -1)
        return dp_cut[c[0]][c[1]][c[2]];
    
   int ans = INT_MAX;
    for (int i = 1; i <= c[0] / 2; i++) {
        int left = slice_cub({i, c[1], c[2]});
        int right = slice_cub({c[0] - i, c[1], c[2]});
        ans = min(ans, left + right + 1);
    }
    
    for (int i = 1; i <= c[1] / 2; i++) {
        int front = slice_cub({c[0], i, c[2]});
        int back = slice_cub({c[0], c[1] - i, c[2]});
        ans = min(ans, front + back + 1);
    }
    
    for (int i = 1; i <= c[2] / 2; i++) {
        int bottom = slice_cub({c[0], c[1], i});
        int top = slice_cub({c[0], c[1], c[2] - i});
        ans = min(ans, bottom + top + 1);
    }
    
    dp_cut[c[0]][c[1]][c[2]] = ans;
    return ans;
}

void solve() {
    cube c;
    cin >> c[0] >> c[1] >> c[2];
    int result = slice_cub(c);
    cout << result + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 초기화
    for (int i = 0; i <= 200; i++) {
        for (int j = 0; j <= 200; j++) {
            for (int k = 0; k <= 200; k++) {
                dp_cut[i][j][k] = -1;
            }
        }
    }

    
    int t;
    cin >> t;
    
    while(t--) {
        solve();
    }
    
    return 0;
}