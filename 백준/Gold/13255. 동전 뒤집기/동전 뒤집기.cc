#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N;
    cin >> K;
    vector<int> A(K);

    for (int i = 0; i < K; i++) cin >> A[i];

    double p = 1.0L; // 특정 동전이 앞면일 확률
    for (int i = 0; i < K; i++) {
        double q = (double)A[i] / (double)N;

        p = p * (1.0 - 2.0 * q) + q;
    }

    double ans = (double)N * p;
    cout << fixed << setprecision(12) << (double)ans << "\n";
    return 0;
}
