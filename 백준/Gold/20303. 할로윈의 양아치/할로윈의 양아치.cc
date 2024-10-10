#include <bits/stdc++.h>

#define REPEAT(N) for(int _ = 0; _ < N; _++)
#define DEBUG false

using namespace std;

int ChildrenCount, ConnectionsCount, MinChildren;
vector<int> Friends;
vector<int> GroupCount;
vector<int> CandyCount;

int Find(int a) {
	if (Friends[a] == a) {
		return a;
	}

	return Friends[a] = Find(Friends[a]);
}

void Union(int a, int b) {
	int a_root = Find(a);
	int b_root = Find(b);

	if (a_root != b_root) {
		Friends[a_root] = b_root;
		GroupCount[b_root] += GroupCount[a_root];
		CandyCount[b_root] += CandyCount[a_root];
		GroupCount[a_root] = -1;
	}
}

int SolveBackpackProblem(const vector<pair<int, int>>& bp, int weight)
{
	if(bp.empty()) return 0;

	vector dp(weight, 0);

	for(const pair<int, int>& item : bp) {
		for(int w = weight - 1; w >= item.first; w--) {
			dp[w] = max(dp[w], dp[w - item.first] + item.second);
		}
	}

	return dp[weight - 1];
}

int main() {
	std::cin >> ChildrenCount >> ConnectionsCount >> MinChildren;

	Friends.resize(ChildrenCount + 1);
	for (int i = 0; i < ChildrenCount + 1; i++) {
		Friends[i] = i;
	}

	GroupCount.resize(ChildrenCount + 1);
	CandyCount.resize(ChildrenCount + 1);
	for (int i = 1; i < ChildrenCount + 1; i++) {
		std::cin >> CandyCount[i];
		GroupCount[i] = 1;
	}

	REPEAT(ConnectionsCount) {
		int a, b;
		std::cin >> a >> b;

		Union(a, b);
	}

	// <childCount, candyCount>
	std::vector<std::pair<int, int>> Backpack;
	for(int g = 1; g <= ChildrenCount; g++) if(GroupCount[g] != -1) {
			if(GroupCount[g] >= MinChildren) continue;

			Backpack.emplace_back(GroupCount[g], CandyCount[g]);
		}

	std::cout << SolveBackpackProblem(Backpack, MinChildren);
}