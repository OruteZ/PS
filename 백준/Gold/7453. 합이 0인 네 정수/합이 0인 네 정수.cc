#include<bits/stdc++.h>

using namespace std;

// 4000 ^ 4 = 256000000000000
// output should be long long

typedef long long ll;

ll countZero(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
    ll ret = 0;

    // O(n^2)
    vector<int> possibleSums(a.size() * b.size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            possibleSums[i * b.size() + j] = a[i] + b[j];
        }
    }
    sort(possibleSums.begin(), possibleSums.end());

    
    // O(n^2 * log(n^2))
    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < d.size(); j++) {
            int target = -c[i] - d[j];

            auto start = lower_bound(possibleSums.begin(), possibleSums.end(), target);
            auto end = upper_bound(possibleSums.begin(), possibleSums.end(), target);

            ret += end - start;
        }
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