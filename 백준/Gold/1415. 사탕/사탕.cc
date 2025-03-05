#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

bool prime[500001];

void buildPrime(){
	memset(prime, true, sizeof(prime));
	prime[0] = prime[1] = false;
	for(int i = 2; i <= 500000; i++){
		if(prime[i]){
			for(int j = i * 2; j <= 500000; j += i)
				prime[j] = false;
		}
	}
}

// 소수 판별 함수 (2부터 sqrt(n)까지 확인)
bool isPrime(int n) {
	return prime[n];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	buildPrime();

	int N;
	cin >> N;

	// 가격별 빈도를 저장
	map<int, int> freq;
	int price;
	int total_sum = 0;
	for(int i = 0; i < N; i++){
		cin >> price;
		freq[price]++;
		total_sum += price;
	}

	// dp[s]: 현재까지 선택한 사탕들의 가격 합이 s가 되는 경우의 수
	// 모든 조합은 모양(가격별 선택 개수)로 구분하므로, 순서와 무관하게 한 번씩만 센다.
	vector<ll> dp(total_sum + 1, 0);
	dp[0] = 1;

	// 각 그룹에 대해 DP 전개: 같은 가격의 사탕이 count개 있다면 0개부터 count개까지 선택할 수 있다.
	for(auto &p : freq){
		int p_val = p.first;
		int count = p.second;
		vector<ll> newdp(total_sum + 1, 0);
		for(int s = 0; s <= total_sum; s++){
			if(dp[s] != 0){
				// 이 그룹에서 k개를 선택하면 총합이 s + k*p_val 가 된다.
				for (int k = 0; k <= count; k++){
					if(s + k * p_val <= total_sum)
						newdp[s + k * p_val] += dp[s];
				}
			}
		}
		dp = newdp;
	}

	// 빈 구매(아무것도 선택하지 않는 경우)는 소수가 될 수 없으므로 s=2부터 확인
	long long ans = 0;
	for (int s = 2; s <= total_sum; s++){
		if(isPrime(s))
			ans += dp[s];
	}

	cout << ans << "\n";
	return 0;
}
