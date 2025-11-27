#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll solve_one_side(vector<pair<int,int>> v, int K) {
    // 가장 먼 거리부터 처리해야 그 왕복(2*d)에 최대한 많은 학생을 실어 올 수 있음
    sort(v.begin(), v.end(), [](auto &a, auto &b){
        return a.first > b.first;
    });

    ll ans = 0;
    int remains = 0;

    for (auto [d, c] : v) {
        // 남은 좌석이 있으면 그만큼 학생 태움
        if (remains > 0) {
            int take = min(remains, c); 
            remains -= take;
            c -= take;
        }
        if (c == 0) continue; 

        // K명씩 꽉 채워서 여러 번 왕복할 수 있는 경우
        int full = c / K;              
        if (full > 0) {
            ans += 2LL * d * full;     
            c -= full * K;             
        }

        // 아직 학생이 남으면 왕복 1번 더 필요
        if (c > 0) {
            ans += 2LL * d;            
            remains = K - c;               
        } else {
            remains = 0;                   
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, S;
    cin >> N >> K >> S;

    // <좌표, 학생 수>
    vector<pair<int,int>> leftSide;   // x < S 인 위치들
    vector<pair<int,int>> rightSide;  // x > S 인 위치들 

    for (int i = 0; i < N; i++) {
        int x, a;
        cin >> x >> a;

        if (x < S) leftSide.emplace_back(S - x, a);
        else if (x > S) rightSide.emplace_back(x - S, a);
    }

    ll ans = solve_one_side(leftSide, K) + solve_one_side(rightSide, K);
    cout << ans << "\n";
    return 0;
}
