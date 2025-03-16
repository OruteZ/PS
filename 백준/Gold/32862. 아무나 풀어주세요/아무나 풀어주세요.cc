#include <bits/stdc++.h>
using namespace std;

inline int encode(int a, int b, int c) {
	return (a-1)*81 + (b-1)*9 + (c-1);
}

inline void decode(int code, int &a, int &b, int &c) {
	a = code / 81 + 1;
	int r = code % 81;
	b = r / 9 + 1;
	c = r % 9 + 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--){
		int N, M;
		cin >> N >> M;
		vector<int> A(N), B(M);
		for (int i = 0; i < N; i++) cin >> A[i];
		for (int j = 0; j < M; j++) cin >> B[j];

		// 만약 초기 수열 A의 앞쪽 (잠긴 부분, 길이 N-3)이 B의 잠긴 부분과 다르면 불가능
		if(N > 3){
			bool ok = true;
			for (int i = 0; i < N-3; i++){
				if(A[i] != B[i]){
					ok = false;
					break;
				}
			}

			if(not ok){
				cout << "NO\n";
				continue;
			}
		}
		
		// 예외 처리
		if(M == N){
			if(A == B) cout << "YES\n";
			else cout << "NO\n";
			continue;
		}

		int mov_cnt = M - N;
		vector<bool> cur(729, false), nxt(729, false);

		// 초기 꼬리
		int initState = encode(A[N-3], A[N-2], A[N-1]);
		cur[initState] = true;

		bool possible = false;
		for (int i = 0; i < mov_cnt; i++){
			fill(nxt.begin(), nxt.end(), false);
			int required = B[(N-3) + i]; // 새로 잠기게 될 숫자
			
			//BFS
			for (int state = 0; state < 729; state++){
				if(not cur[state]) continue;
				int x, y, z;
				decode(state, x, y, z);
				if(x == required){
					for (int d = 1; d <= 9; d += 2){ // 홀수만
						int ns = encode(y, z, d);
						nxt[ns] = true;
					}
				}
				
				
				int a = x, b = y, c = z;
				// 3개 정렬
				if(a > b) swap(a,b);
				if(b > c) swap(b,c);
				if(a > b) swap(a,b);
				
				if(a == required){
					for (int d = 2; d <= 8; d += 2){ // 짝수만
						int ns = encode(b, c, d);
						nxt[ns] = true;
					}
				}
			}
			cur.swap(nxt);
		}
		
		// 마지막 상태가 B의 마지막 상태와 같은지 확인
		int finalState = encode(B[M-3], B[M-2], B[M-1]);
		cout << (cur[finalState] ? "YES" : "NO") << "\n";
	}
	return 0;
}
