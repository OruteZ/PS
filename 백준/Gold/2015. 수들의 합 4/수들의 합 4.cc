#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> preSum(n);
	map<int, ll> sumFreq;
	sumFreq[0] = 1;

	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;
		if (i == 0) {
			preSum[i] = num;
		} else {
			preSum[i] = preSum[i - 1] + num;
		}
	}



	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (sumFreq.find(preSum[i] - k) != sumFreq.end()) {
			ans += sumFreq[preSum[i] - k];
		}

		sumFreq[preSum[i]]++;
	}

	cout << ans << endl;
}