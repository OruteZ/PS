#include <bits/stdc++.h>

using namespace std;

inline int mod(int a) {
	if(a < 0) a += 10000;
	return a % 1000;
}

inline int clamp(int a) {
	return max(0, a);
}

int main()
{
	int adult_day;
	int end_prod_day;
	int die_day;
	int target_day;

	cin >> adult_day >> end_prod_day >> die_day >> target_day;

	// 누적합은 0번 index 비우고 1번 index부터 시작해야 깔끔
	// 0일차부터 target_day일차까지의 벌레 수를 구해야함
	// 1일차에서 시작한다고 보고 target_day 1증가
	target_day++;

	// 기간 1 : 성체가 되고있는 과정의 벌레 수 = 이전 기간 재생산중인 벌레 수를 적당히 더하면 됨
	// 기간 2 : 성체가 된 후 재생산중인 벌레 수 = 자라서 성체가 된 놈들
	// 기간 3 : 재생산을 멈춘 벌레들

	// dp[0][cur_time] = sigma(cur_time - adult_day + 1, cur_time + 1, dp[1]);
	// dp[1][cur_time] = sigma(cur_time - end_prod_day + 1, cur_time - adult_day + 1, dp[1])
	// dp[2][cur_time] = sigma(cur_time - die_day + 1, cur_time - end_prod_day + 1, dp[1]);

	// sigma로 통일되어있는거보니 누적합으로 구할 수 있어보이는데
	// dp[i] = 당일 생산 된 벌레 수의 누적 합
	vector dp(target_day + 1, 0);
	dp[0] = 0;
	dp[1] = 1; // 1일차에 임의로 벌레 추가

//	cout << 1 << ' ';
	for(int cur_time = 2; cur_time <= target_day; cur_time++)
	{
		int start = clamp(cur_time - end_prod_day);
		int end = clamp(cur_time - adult_day);

		int created_today = mod(dp[end] - dp[start]);

		dp[cur_time] = mod(dp[cur_time - 1] + created_today);

//		cout << created_today << " ";
	}
//	cout << endl;

	// print
//	for(int i = 1; i <= target_day; i++) {
//		cout << dp[i] << " ";
//	} cout << endl;

	int all = mod(dp[target_day] - dp[clamp(target_day - die_day)]);
	cout << all << endl;
}