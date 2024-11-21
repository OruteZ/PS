#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef map<tuple<int, int, int>, ll> dp_t;

ll inline MOD(ll n) {
	return n % 1'000'000'000;
}

ll recursion(int idx, int num, bitset<10> used, dp_t& dp) {
	if(num < 0 or num > 9) {
		return 0;
	}

	used.set(num);

	if(idx == 0) {
		return used.all() ? 1 : 0;
	}

	if(dp.find({idx, num, used.to_ulong()}) != dp.end()) {
		return dp[{idx, num, used.to_ulong()}];
	}

	ll ans =
		MOD(
			recursion(idx - 1, num + 1, used, dp) +
			recursion(idx - 1, num - 1, used, dp)
		);

	dp[{idx, num, used.to_ulong()}] = ans;
	return ans;
}

ll getStairNums(int n) {
	dp_t dp;

	ll ans = 0;
	for(int i = 1; i < 10; i++) {
		bitset<10> used;
		used.set(i);
		ans = MOD(ans + recursion(n - 1, i, used, dp));
	}

	return ans;
}

int main() {
	int n;
	cin >> n;

	cout << getStairNums(n) << endl;
}