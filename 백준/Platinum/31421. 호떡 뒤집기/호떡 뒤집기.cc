#include <bits/stdc++.h>

using namespace std;

int main() {
	int n; cin >> n;
	string target; cin >> target;

	vector<int> changes; // target[x]와 target[x+1]이 달라지는 모든 x 저장
	for (int i = 0; i < n - 1; i++) {
		if (target[i] != target[i + 1]) {
			changes.push_back(i);
		}
	}

	if(target.back() == 'W') {
		cout << changes.size() << '\n';
		for (int change : changes) {
			cout << change + 1 << '\n';
		}
		return 0;
	}


	// target.back() == 'B'
	if(changes.size() % 2 == 1) {
		if(changes.size() == 1) {
			cout << -1 << '\n';
			return 0;
		}

		// [-1]과 [-2]의 값 swap
		swap(changes[changes.size() - 1], changes[changes.size() - 2]);

		// 오름차순 출력
		cout << changes.size() << '\n';
		for (int change : changes) {
			cout << change + 1 << '\n';
		}

		return 0;
	}

	if(changes.empty()) {
		cout << -1 << '\n';
		return 0;
	}
	
	cout << changes.size() << '\n';
	// 내림차순 출력
	for (int i = changes.size() - 1; i >= 0; i--) {
		cout << changes[i] + 1 << ' ';
	}
}