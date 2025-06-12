#include<bits/stdc++.h>

using namespace std;

bool isMonge(const vector<vector<int>>& arr, int n, int m) {
	for(int i = 0; i < n - 1; i++) {
		for(int j = 0; j < m - 1; j++) {
			int less = arr[i][j] + arr[i + 1][j + 1];
			int more = arr[i + 1][j] + arr[i][j + 1];

			if(less > more) return false;
		}
	}
	return true;
}

void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>>arr(n, vector<int>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	if(isMonge(arr, n, m)) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}

int main() {
	int t_case;

	cin >> t_case;
	while(t_case--) {
		solve();
	}
}