#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

double dp[10000];
double func(vector<double> &arr, int idx) {
    if(idx == arr.size() - 1) return arr[idx];

    double &answer = dp[idx];
    answer = max(func(arr, idx + 1) * arr[idx], arr[idx]);

    return answer;
}

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<double> arr(n);

    for(double &f : arr) {
        cin >> f;
    }

    func(arr, 0);

    cout << fixed;
    cout.precision(3);

    cout << *max_element(dp, dp + n - 1) << endl;

//    for(int i = 0; i < n; i++) {
//        cout << dp[i] << " ";
//    }

    return 0;
}