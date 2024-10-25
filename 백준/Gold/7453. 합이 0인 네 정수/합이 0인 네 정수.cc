#include<bits/stdc++.h>

using namespace std;

// 4000 ^ 4 = 256000000000000
// output should be long long

typedef long long ll;

ll countZero(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
    ll ret = 0;

    // O(n^2)
    vector<int> possible_sums(a.size() * b.size());
    vector<int> possible_sums2(c.size() * d.size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            possible_sums[i * b.size() + j] = a[i] + b[j];
            possible_sums2[i * b.size() + j] = c[i] + d[j];
        }
    }
    sort(possible_sums.begin(), possible_sums.end());
    sort(possible_sums2.begin(), possible_sums2.end());


    
    // O(n^2)
    for (int i = 0; i < possible_sums.size(); i++) {
        int target = -possible_sums[i];
        auto range = equal_range(possible_sums2.begin(), possible_sums2.end(), target);
        ret += range.second - range.first;
    }

    return ret;
}


int main() {
    int n; cin >> n;

    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    cout << countZero(a, b, c, d) << endl;

    return 0;
}