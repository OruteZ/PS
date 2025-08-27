#include <bits/stdc++.h>

using namespace std;

int LisLength(const vector<int>& a) {

    vector<int> d;

    for (int x : a) {

        auto it = lower_bound(d.begin(), d.end(), x);

        if (it == d.end()) d.push_back(x);

        else *it = x;

    }

    return (int)d.size();

}

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int N; 

    cin >> N;

    vector<int> a(N);

    for (int i = 0; i < N; ++i) cin >> a[i];

    cout << N - LisLength(a) << '\n';

    return 0;

}

