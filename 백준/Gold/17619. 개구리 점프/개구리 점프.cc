#include <bits/stdc++.h>

using namespace std;

int main() {
	// fast io
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int woods_cnt;
	int q_cnt;

	cin >> woods_cnt >> q_cnt;

	vector<tuple<int, int, int>> woods(woods_cnt);
	vector<int> group(woods_cnt); // group[i] = i번째 나무가 속한 그룹 번호

	int x1, x2, y;
	for(int i = 0; i < woods_cnt; i++) {
		cin >> x1 >> x2;
		woods[i] = {x1, x2, i};
		cin >> y; // y는 입력받고 버림. 스위핑 해버릴꺼라서
	}

	sort(woods.begin(), woods.end());
	int group_num = 0, last_position = -1;
	for(int i = 0; i < woods_cnt; i++) {
		auto [left, right, idx] = woods[i];

		// 끊어져있다면 다음 그룹으로 그룹 증가
		if(left > last_position) {
			group_num++;
		}
		group[idx] = group_num;
		last_position = max(last_position, right);
	}

	for(int i = 0; i < q_cnt; i++) {
		int a, b;
		cin >> a >> b;

		cout << ((group[a - 1] == group[b - 1]) ? 1 : 0) << '\n';
	}
}