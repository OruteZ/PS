#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MOD(N) ((N) % 1000000007)
#define MATRIX std::vector<std::vector<LL>>

MATRIX arr = {
	{0, 1, 0, 0, 1, 0 ,0, 0},
	{1, 0, 1, 0, 1, 0, 0, 0},
	{0, 1, 0, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 0, 1, 1, 0},
	{1, 1, 1, 0, 0, 0, 1, 0},
	{0, 0, 0, 1, 0, 0, 0, 1},
	{0, 0, 1, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 1, 1, 0}
};

MATRIX operator*(const MATRIX &A, const MATRIX &B) {
	MATRIX ret(8, std::vector<LL>(8, 0));
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			for(int k = 0; k < 8; k++) {
				ret[i][j] = MOD(ret[i][j] + MOD(A[i][k] * B[k][j]));
			}
		}
	}
	return ret;
}

MATRIX pow(MATRIX matrix, LL n) {
	MATRIX ret(8, std::vector<LL>(8, 0));
	for(int i = 0; i < 8; i++) {
		ret[i][i] = 1;
	}
	
	while(n > 0) {
		if(n % 2 == 1) {
			ret = ret * matrix;
		}
		matrix = matrix * matrix;
		n /= 2;
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);std::cout.tie(nullptr);

	LL n; cin >> n;
	MATRIX result = pow(arr, n);
	cout << result[0][0];

	return 0;
}

