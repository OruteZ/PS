#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int solve(const vector<int>& stones) {
	vector<vector<int>> remains(stones.size());
	for (int i = 0; i < stones.size(); i++){
		remains[i].push_back(stones[i]);
	}

	int answer = (int)stones.size();
	for (int i = 1; i < stones.size(); i++){
		for (auto st : remains[i - 1]) {
			if (stones[i] > st) {
				remains[i].push_back(stones[i] - st);
			}

			else if (stones[i] == st) {
				remains[i].clear();
				answer--;
				break;
			}
		}
	}

	return answer;
}

int main(){
	int n;
	cin >> n;
	vector<int> stones(n);
	for (int i = 0; i < n; i++){
		cin >> stones[i];
	}

	cout << solve(stones) << "\n";
	return 0;
}
