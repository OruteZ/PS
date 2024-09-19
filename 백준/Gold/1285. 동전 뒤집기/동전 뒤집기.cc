#include <bits/stdc++.h>

using namespace std;


// ================== 변수 정의 ==================
#define MAX 20
int N;
bitset<MAX> Board[MAX];

// answer 관련
int Answer = 987654321;

void Init() {
	cin >> N;

	char c;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> c;

			Board[i][N - j - 1] = c == 'H';
		}
	}


}

int main() {
	Init();

	bitset<MAX> mask;
	for(int m = 0; m < (1 << N); m++) {
		mask = m;

		int curResult = 0;

		for(int i = 0; i < N; i++) {
			//mask와 Board[i]를 XOR 연산
			bitset<MAX> temp = mask ^ Board[i];

			int oneCount = temp.count();
			int zeroCount = N - oneCount;

			curResult += min(oneCount, zeroCount);
		}

		Answer = min(Answer, curResult);
	}

	cout << Answer << endl;

	return 0;
}