#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
	int divisor, size;
	cin >> divisor >> size;

	ll answer = 0;
	vector<ll> freq(divisor, 0);
	freq[0] = 1;              // prefix_sum[0] == 0 의 나머지 0 카운트

	ll prefix_mod = 0;
	for (int i = 0; i < size; i++) {
		int x;
		cin >> x;
		prefix_mod = (prefix_mod + x) % divisor;
		// 마이너스가 나올 수도 있으니
		if (prefix_mod < 0)
			prefix_mod += divisor;

		// 지금까지 이 나머지를 가진 prefix가 freq[prefix_mod]개 있었으므로
		// 이들 각각과 현재 prefix를 짝지으면 연속합이 나누어떨어짐
		answer += freq[prefix_mod];

		// 이제 이 prefix도 카운트에 추가
		freq[prefix_mod]++;
	}

	cout << answer << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t_case;
	cin >> t_case;
	while (t_case--) {
		solve();
	}
	return 0;
}
