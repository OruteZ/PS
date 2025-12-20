#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<int,int>> a(N); // (h, k)
    for (int i = 0; i < N; i++) cin >> a[i].first >> a[i].second;

    // 키 내림차순
    sort(a.begin(), a.end(), [](auto &x, auto &y){
        return x.first > y.first;
    });

    multiset<int> teams; // 각 팀의 현재 인원수
    for (auto &[h, k] : a) {
        auto it = teams.lower_bound(k); // first size >= k
        if (it == teams.begin()) {
            // size < k인 팀이 없다 -> 새 팀 생성
            teams.insert(1);
        } else {
            // prev(it)가 size < k 중 가장 큰 팀
            --it;
            int sz = *it;
            teams.erase(it);
            teams.insert(sz + 1);
        }
    }

    cout << teams.size() << "\n";
    return 0;
}
