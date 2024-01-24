#include <iostream>
#include <cmath> 
#pragma warning(disable:4996)
#pragma warning(disable:6031)
using namespace std;

#define MAX_NM 500

int n, m, arr[MAX_NM][MAX_NM], dp[MAX_NM][MAX_NM];

const int dx[4] = { 0, 0, 1, -1 };
const int dy[4] = { 1, -1, 0, 0 };

void check(int x0, int y0) {
	int cnt = 0;

	for (int d = 0; d < 4; d++) {
		int x = x0 + dx[d];
		int y = y0 + dy[d];

		if (x < 0 || x >= n || y < 0 || y >= m) continue;

		if (arr[x][y] > arr[x0][y0]) cnt += dp[x][y];
	}

	dp[x0][y0] = max(dp[x0][y0], cnt);
}

int main() {

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	dp[0][0] = 1;

	//최초 전파
	for (int x0 = 0; x0 < n; x0++) {
		for (int y0 = 0; y0 < m; y0++) {
			check(x0, y0);
		}
	}

	int max = n > m ? n : m;

	for (int i = 0; i < (max - 1) / 2; i++) {

		//역방향 전파
		for (int x0 = n - 1; x0 >= 0; x0--) {
			for (int y0 = m - 1; y0 >= 0; y0--) {
				check(x0, y0);
			}
		}

		//정방향 전파
		for (int x0 = 0; x0 < n; x0++) {
			for (int y0 = 0; y0 < m; y0++) {
				check(x0, y0);
			}
		}
	}

	printf("%d", dp[n - 1][m - 1]);

	return 0;
}