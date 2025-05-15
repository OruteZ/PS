#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;

    vector<ll> A(N);
    ll totalSum = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        totalSum += A[i];
    }

    // 전체 사이클 건너뛰기
    ll rem = M % totalSum;

    // 현재 따갈 수 있는 곰곰이들만 큐에 넣고 합 계산
    deque<ll> dq;
    ll sumQ = 0;
    for (ll a : A) {
        if (a <= rem) {
            dq.push_back(a);
            sumQ += a;
        }
    }

    // 아무도 땄을 때 남는 귤
    if (dq.empty()) {
        cout << rem;
        return 0;
    }

    // 한 번 더 풀 사이클 건너뛰기
    if (sumQ > 0) rem %= sumQ;

    // 시뮬레이션: 남은 곰곰이가 1명 이하이거나 rem이 0이 될 때까지
    while (dq.size() > 1 && rem > 0 && sumQ > 0) {
        ll cur = dq.front(); dq.pop_front();
        if (cur <= rem) {
            rem -= cur;
            dq.push_back(cur);
        } else {
            sumQ -= cur;
            if (sumQ > 0)
                rem %= sumQ;
            else
                break;
        }
    }

    // 최종 결과
    ll ans;
    if (rem == 0) {
        ans = 0;
    } else if (sumQ == 0) {
        ans = rem;
    } else {
        ans = rem % dq.front();
    }
    cout << ans;
    return 0;
}
