#include<bits/stdc++.h>

using namespace std;
typedef long long int ll;


int main(){
	vector<int> result;
	vector<vector<int>> prepare_matrix;

	int n;
	cin >> n;

	prepare_matrix.resize(n, vector<int>(n, 0));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> prepare_matrix[i][j];
		}
	}

	// 1. 기본 조건 검증: 대각원소는 0, i != j일 때 A[i][j]는 1 또는 -1, 그리고 A[i][j] = -A[j][i]
	for(int i = 0; i < n; i++){
		if(prepare_matrix[i][i] != 0){
			cout << -1 << "\n";
			return 0;
		}
		for(int j = 0; j < n; j++){
			if(i == j) continue;
			if(prepare_matrix[i][j] != 1 and prepare_matrix[i][j] != -1){
				cout << -1 << "\n";
				return 0;
			}
			if(prepare_matrix[i][j] == 1 and prepare_matrix[j][i] != -1){
				cout << -1 << "\n";
				return 0;
			}
			if(prepare_matrix[i][j] == -1 and prepare_matrix[j][i] != 1){
				cout << -1 << "\n";
				return 0;
			}
		}
	}

	// 각 줄의 1의 개수로 reslut에 저장
	for(int i = 0; i < n; i++){
		int cnt = 0;
		for(int j = 0; j < n; j++){
			if(prepare_matrix[i][j] == -1){
				cnt++;
			}
		}
		result.push_back(cnt + 1);
	}

	// result배열로 prepare_matrix만들어보고 일치비교
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j) continue;
			if(prepare_matrix[i][j] == 1 and result[i] >= result[j]){
				cout << -1 << "\n";
				return 0;
			}
			if(prepare_matrix[i][j] == -1 and result[i] <= result[j]){
				cout << -1 << "\n";
				return 0;
			}
		}
	}

	vector<bool> used(n+1, false);
	for(int i = 0; i < n; i++){
		int val = result[i];
		if(val < 1 || val > n || used[val]){
			cout << -1 << "\n";
			return 0;
		}
		used[val] = true;
	}

	// 일치하면 result 출력
	for(int i = 0; i < n; i++){
		cout << result[i] << " ";
	}
}