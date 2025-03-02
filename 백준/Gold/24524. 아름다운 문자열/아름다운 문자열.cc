#include <bits/stdc++.h>

using namespace std;

// 각 알파벳의 위치를 표현하는 큐
map<char, queue<int>> IndexInfo;

int main() {
	string T, S;
	cin >> S >> T;

	// 각 알파벳의 위치를 저장
	for (int i = 0; i < S.size(); i++) {
		IndexInfo[S[i]].push(i);
	}

	// T를 몇개나 구성할 수 있는지 구현
	int count = -1;
	for(bool find = true; find; count++) {
		int last_idx = -1;
		for(char target : T) {
			FIND: // goto를 쓰는 날이 오다니... continue를 쓰면 target알파벳이 바뀌기때문에 안됨
			
			// 해당 알파벳이 없다면 불가능
			if(IndexInfo[target].empty()) {
				find = false;
				break;
			}


			// 해당 알파벳이 존재한다면
			int idx = IndexInfo[target].front();
			IndexInfo[target].pop();

			// 해당 알파벳이 존재하는 위치가 이전 알파벳의 위치보다 작다면 불가능
			if(idx < last_idx) {
				goto FIND;
			}

			last_idx = idx;
		}
	}

	cout << count << endl;
}