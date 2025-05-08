#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// memoization
int dp_cut[205][205][205];

int slice_cub(int a, int b, int c) {
    // a, b, c를 오름차순으로 정렬: a <= b <= c
    if(a > b) swap(a, b);
    if(b > c) swap(b, c);
    if(a > b) swap(a, b);
    
    // 정육면체인 경우
    if(a == b && b == c) {
        dp_cut[a][b][c] = 0;
        return 0;
    }
    if(dp_cut[a][b][c] != -1)
        return dp_cut[a][b][c];
    
    int ans = INT_MAX;
    
    for (int i = 1; i <= a / 2; i++) {
        int left = slice_cub(i, b, c);
        int right = slice_cub(a - i, b, c);
        ans = min(ans, left + right + 1);
    }
    
    for (int i = 1; i <= b / 2; i++) {
        int front = slice_cub(a, i, c);
        int back = slice_cub(a, b - i, c);
        ans = min(ans, front + back + 1);
    }
    
    for (int i = 1; i <= c / 2; i++) {
        int bottom = slice_cub(a, b, i);
        int top = slice_cub(a, b, c - i);
        ans = min(ans, bottom + top + 1);
    }
    
    dp_cut[a][b][c] = ans;
    return ans;
}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    int result = slice_cub(a, b, c);
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