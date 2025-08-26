#include <bits/stdc++.h>
using namespace std;

int N;
vector<array<int, 3>> Rgb;          
vector<array<int, 3>> Memo;         

int dp(int index, int color) {
	if (index == 0) return Rgb[0][color];
	int &ret = Memo[index][color];
	if (ret != -1) return ret;

	int c1 = (color + 1) % 3;
	int c2 = (color + 2) % 3;
	ret = Rgb[index][color] + min(dp(index - 1, c1), dp(index - 1, c2));
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	Rgb.resize(N);
	Memo.assign(N, { -1, -1, -1 });

	for (int i = 0; i < N; ++i) {
		int r, g, b;
		cin >> r >> g >> b;
		Rgb[i] = { r, g, b };
	}

	int ans = min({ dp(N - 1, 0), dp(N - 1, 1), dp(N - 1, 2) });
	cout << ans << '\n';
	return 0;
}
