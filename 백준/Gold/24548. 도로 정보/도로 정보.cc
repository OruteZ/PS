#include <bits/stdc++.h>

using namespace std;
using ll = long long;

inline void Renew(char c, int& t, int& g, int& f, int& p) {
	if(c == 'T') {t++; t%=3;}
	else if(c == 'G') {g++; g%=3;}
	else if(c == 'F') {f++; f%=3;}
	else if(c == 'P') {p++; p%=3;}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int presum[3][3][3][3] ;
	fill_n(&presum[0][0][0][0], 3*3*3*3, 0);
	presum[0][0][0][0] = 1; // 초기값


	int n;
	cin >> n;

	int t = 0, g = 0, f = 0, p = 0;

	while(n--) {
		char c;
		cin >> c;

		Renew(c, t, g, f, p);
		presum[t][g][f][p]++;
	}

	//debug: print
//	for(int t1 = 0; t1 < 3; t1++) {
//		for(int g1 = 0; g1 < 3; g1++) {
//			for(int f1 = 0; f1 < 3; f1++) {
//				for(int p1 = 0; p1 < 3; p1++) {
//					if(presum[t1][g1][f1][p1] == 0) continue;
//					cerr << "presum[" << t1 << "][" << g1 << "][" << f1 << "][" << p1 << "] = " << presum[t1][g1][f1][p1] << '\n';
//				}
//			}
//		}
//	}

	// 모든 경우의 수에 대해서 Comb(val, 2) 계산
	ll result = 0;
	for(int t1 = 0; t1 < 3; t1++) {
		for(int g1 = 0; g1 < 3; g1++) {
			for(int f1 = 0; f1 < 3; f1++) {
				for(int p1 = 0; p1 < 3; p1++) {
					int val = presum[t1][g1][f1][p1];
					result += (ll)val * (val - 1) / 2;
				}
			}
		}
	}

	cout << result << '\n';
}
