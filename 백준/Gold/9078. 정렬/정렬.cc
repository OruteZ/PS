#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> a(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }

        long long inv = 0;
        // 인버전 수 계산
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (a[i] > a[j]) 
                    inv++;
            }
        }

        // 짝수면 YES, 홀수면 NO
        cout << (inv % 2 == 0 ? "YES\n" : "NO\n");
    }
    return 0;
}