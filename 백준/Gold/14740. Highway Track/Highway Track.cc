#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> o(N), d(N);
    for (int i = 0; i < N; i++) {
        cin >> o[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> d[i];
    }

    vector<ll> diff(N);
    for (int i = 0; i < N; i++) {
        diff[i] = o[i] - d[i];
    }

    // P[i] = diff[0] + diff[1] + ... + diff[i-1]
    vector<ll> P(2 * N + 1, 0LL);
    for (int i = 1; i <= 2 * N; i++) {
        P[i] = P[i - 1] + diff[(i - 1) % N];
    }


    // 슬라이딩 윈도우우
    deque<int> dq;
    ll count_valid = 0;

    for (int i = 1; i <= 2 * N; i++) {
        // 오름차순 유지 위해서 pop back
        while (not dq.empty() and P[dq.back()] >= P[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        int window_start = i - N + 1;
        if (not dq.empty() and dq.front() < window_start) {
            dq.pop_front();
        }

        if (i > N and i <= 2 * N) {
            int b = i - N;
            ll window_min = P[dq.front()];
            ll base       = P[b];           
            if (window_min >= base) {
                count_valid++;
            }
        }
    }

    cout << count_valid << "\n";
    return 0;
}
