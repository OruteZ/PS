#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
static const int MAX = 1500;

int R, C;
// 사과(A) 배열, 바나나(B) 배열
int A[MAX+1][MAX+1], B[MAX+1][MAX+1];
// 행 누적 합
int Apre[MAX+1][MAX+1];
int Bpre[MAX+1][MAX+1];

// dp[r][c]: (1,1)에서 출발하여 r행의 경계열이 c일 때 얻을 수 있는 최대 이익
ll dp[MAX+1][MAX+1];

// [r][c]에서 가를떄 위아래 합
inline ll getSum(int r, int c){
	return (Apre[R][c] - Apre[r][c]) +
			Bpre[r - 1][c];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> R >> C;

	// 1. 입력받아 A, B 배열 채우기
	char kind;
	int num;
	for(int r = 1; r <= R; r++){
		for(int c = 1; c <= C; c++){
			cin >> kind >> num;

			if(kind == 'A'){
				A[r][c] = num;
				B[r][c] = 0;
			} else {
				A[r][c] = 0;
				B[r][c] = num;
			}
		}
	}

	// 2. 행별 누적 합 Apre, Bpre
	for(int c = 1; c <= C; c++){
		Apre[1][c] = A[1][c];
		Bpre[1][c] = B[1][c];

		for(int r = 2; r <= R; r++){
			Apre[r][c] = Apre[r-1][c] + A[r][c];
			Bpre[r][c] = Bpre[r-1][c] + B[r][c];
		}
	}

	// 3. DP 진행
	// dp 테이블 초기화
	for(int r = 1; r <= R; r++){
		for(int c = 1; c <= C; c++){
			dp[r][c] = -1e15; // 매우 작은 값으로 초기화
		}
	}

	// (1,1) 초기값
	// cost(1,1) = Apre[1][0] + (Bpre[1][C] - Bpre[1][1])
	dp[1][1] = getSum(1, 1);

	// 첫 행 초기화: r=1, c=2..C
	for(int c = 2; c <= C; c++){
		dp[1][c] = dp[1][c-1] + getSum(1, c);
	}

	// 첫 열 초기화: c=1, r=2..R
	for(int r = 2; r <= R; r++){
		dp[r][1] = dp[r-1][1] - A[r][1];
	}

	// 일반 DP 채우기
	for(int c = 2; c <= C; c++) {
		for(int r = 2; r <= R; r++) {
			// 1. 왼쪽(위)에서 올 때
			dp[r][c] = max(dp[r][c], dp[r][c-1] + getSum(r, c));
			dp[r][c] = max(dp[r][c], dp[r-1][c-1] + getSum(r, c));

			// 2. 위에서 올 때
			dp[r][c] = max(dp[r][c], dp[r-1][c] - A[r][c]);
		}
	}

	// test dp print
//	for(int r = 1; r <= R; r++){
//		for(int c = 1; c <= C; c++){
//			cout << dp[r][c] << " ";
//		}
//		cout << "\n";
//	}

	// 4. 결과 출력
	cout << dp[R][C] << "\n";

	return 0;
}
