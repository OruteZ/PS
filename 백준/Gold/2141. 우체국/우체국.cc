#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<ll, ll>> v; // {위치 x, 인구 a}
    v.reserve(N);

    for (int i = 0; i < N; ++i) {
        ll x, a;
        cin >> x >> a;
        v.push_back({x, a});
    }

    // 위치 기준 정렬
    sort(v.begin(), v.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.first != rhs.first) return lhs.first < rhs.first;
        return lhs.second < rhs.second;
    });

    // 전체 인구 합
    ll total = 0;
    for (const auto& p : v) {
        total += p.second;
    }

    ll half = (total + 1) / 2;
    ll acc = 0;
    ll answer = v.back().first;

    // 누적 인구가 half 이상이 되는 첫 위치가 가중 중앙값
    for (const auto& p : v) {
        acc += p.second;
        if (acc >= half) {
            answer = p.first;
            break;
        }
    }

    cout << answer << "\n";
    return 0;
}
