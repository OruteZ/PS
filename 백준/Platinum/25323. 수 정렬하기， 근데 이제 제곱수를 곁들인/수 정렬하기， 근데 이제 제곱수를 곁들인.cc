#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

#define BIG 10000000000

ll get_gcd(ll a, ll b) {
    if(a < b) {
        swap(a, b);
    }

    while(true) {
        ll mod = a % b;
        if(mod == 0) return b;

        a = b;
        b = mod;
    }
}

bool is_square(long long x, long long s = 0, long long e = (1LL << 31)) {
    if(e - s <= 1) {
        return (s * s == x or e * e == x);
    }

    long long mid = (s + e) / 2;
    if(mid * mid <= x) {
        return is_square(x, mid, e);
    }
    else {
        return is_square(x, s, mid);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<ll> nums(n);
    for(ll &i : nums) cin >> i;

    vector<ll> sorted_nums(nums);
    sort(sorted_nums.begin(), sorted_nums.end());

    for(int i = 0; i < n; i++) {
        ll b = nums[i];
        ll a = sorted_nums[i];

        ll g = get_gcd(a, b);

        if(not is_square(b / g)) {
            cout << "NO";
            exit(0);
        }

        if(not is_square(a / g)) {
            cout << "NO";
            exit(0);
        }
    }

    cout << "YES";
}

