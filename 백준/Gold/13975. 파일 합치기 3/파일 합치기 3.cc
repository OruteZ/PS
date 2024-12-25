#include <bits/stdc++.h>
void solve();
using namespace std;

// 아니쇼발
// 소설이면 순서를 맞춰서 인접한 애들끼리 합쳐야 하는거 아니었냐고

typedef long long ll;

int main() {
	int t_case; cin >> t_case;
	while(t_case--) {
		solve();
	}
}
void solve()
{
	priority_queue<ll, deque<ll>, greater<>> pq;

	int n; cin >> n;

	for(int i = 0; i < n; i++) {
		int x; cin >> x;
		pq.push(x);
	}

	ll answer = 0;

	while(pq.size() > 1) {
		// 가장 큰 두 수를 빼서 더한 뒤 다시 넣는다.
		ll a = pq.top(); pq.pop();
		ll b = pq.top(); pq.pop();

		answer += a + b;

		pq.push(a + b);
	}

	cout << answer << '\n';
}

