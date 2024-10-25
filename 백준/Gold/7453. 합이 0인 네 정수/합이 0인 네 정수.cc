#include<bits/stdc++.h>

using namespace std;

// 4000 ^ 4 = 256000000000000
// output should be long long

typedef long long ll;

ll countZero(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
    ll ret = 0;

    // O(n^2)
    vector<int> possibleSums(a.size() * b.size());
    vector<int> possibleSums2(c.size() * d.size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            possibleSums[i * b.size() + j] = a[i] + b[j];
            possibleSums2[i * b.size() + j] = c[i] + d[j];
        }
    }
    sort(possibleSums.begin(), possibleSums.end());
    sort(possibleSums2.begin(), possibleSums2.end());


    
    // O(n^2)
    for (int i = 0; i < possibleSums.size(); i++) {
        int target = -possibleSums[i];
        auto range = equal_range(possibleSums2.begin(), possibleSums2.end(), target);
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