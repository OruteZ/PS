#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 10000;

vector<long long> coords;      // 좌표 압축용 (l, r를 모두 담고 중복 제거)
vector<int> compL, compR;      // 포스터별로 압축된 좌표 (왼쪽, 오른쪽)

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<pair<int, int>> posters(n);

	coords.reserve(n*2);
	for(int i=0; i<n; i++){
		cin >> posters[i].first >> posters[i].second;
		// 문제에서 (l < r) 보장
		coords.push_back(posters[i].first);
		coords.push_back(posters[i].second);
	}

	//좌표 압축
	sort(coords.begin(), coords.end());
	coords.erase(unique(coords.begin(), coords.end()), coords.end());
	// coords[k] : 압축 풀었을 때의 실제 좌표

	auto idxOf = [&](int x){
	  return int(std::lower_bound(coords.begin(), coords.end(), x) - coords.begin());
	};

	compL.resize(n);
	compR.resize(n);
	for(int i=0; i<n; i++){
		compL[i] = idxOf(posters[i].first);
		compR[i] = idxOf(posters[i].second);
	}


	// 2) 덮기
	vector<int> covered(coords.size(), -1);
	for(int i=0; i<n; i++){
		for(int j = compL[i]; j <= compR[i]; j++){
			covered[j] = i + 1;
		}
	}

	// 3) covered 개수 세기
	int res = 0;
	vector<bool> visited(n, false);
	for(int i : covered){
		if(i == -1) continue;
		if(!visited[i]){
			visited[i] = true;
			res++;
		}
	}

	cout << res << '\n';

	return 0;
}
