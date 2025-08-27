#include <bits/stdc++.h>

using namespace std;

bool CanPartition(const vector<int>& a, int M, int mid) {

    int segments = 1;

    int curMin = a[0], curMax = a[0];

    for (int i = 1; i < (int)a.size(); ++i) {

        curMin = min(curMin, a[i]);

        curMax = max(curMax, a[i]);

        if (curMax - curMin > mid) {

            ++segments;

            if (segments > M) return false;

            curMin = curMax = a[i];

        }

    }

    return true;

}

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int N, M;

    cin >> N >> M;

    vector<int> a(N);

    for (int i = 0; i < N; ++i) cin >> a[i];

    int lo = 0;

    int hi = *max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end());

    while (lo < hi) {

        int mid = (lo + hi) / 2;

        if (CanPartition(a, M, mid)) hi = mid;

        else lo = mid + 1;

    }

    cout << lo << '\n';

    return 0;

}

