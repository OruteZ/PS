#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

ll dp[500][500];

void init() {
    for(auto &i : dp) for(ll &j : i) j = 0;
}

ll merge_file(const vector<int> &file, int begin, int end) {
    if(dp[begin][end] != 0) return dp[begin][end];

    ll &result = dp[begin][end];

    if(begin == end) return result = 0;
    if(begin + 1 == end) return result = file[begin] + file[end];

    ll total = 0; for(int i = begin; i <= end; i++) total += file[i];

    result = INT64_MAX;
    for(int mid = begin; mid < end; mid++) {
        ll l_value = merge_file(file, begin, mid);
        ll r_value = merge_file(file, mid + 1, end);

        result = min(result, l_value + r_value + total);
    }

    return result;
}

void solve() {
    init();
    int k; cin >> k;

    vector<int> files(k);
    for(int &i : files) cin >> i;

    cout << merge_file(files, 0, k - 1) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int t_case; cin >> t_case;
    while(t_case--) {
        solve();
    }

    return 0;
}

