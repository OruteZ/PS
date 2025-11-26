#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll L;
    int N, K;
    cin >> L >> N >> K;

    queue<ll> q;
    unordered_map<ll, bool> visited;

    for(int i = 0; i < N; i++) {
        ll lamp; cin >> lamp;

        // 0 : 가로등 위치 출력
        if(K > 0)
        {
            cout << 0 << '\n';
            K--;
        }

        q.push(lamp);
        visited[lamp] = true;
    }

    ll lv = 1;
    while(not q.empty() && K > 0) {
        int q_size = q.size();
        while(q_size--) {
            ll cur = q.front(); q.pop();
            ll next[2] = {cur - 1, cur + 1};

            if(cur > 0 && not visited[next[0]]) {
                visited[next[0]] = true;
                q.emplace(next[0]);

                if(K > 0)
                {
                    cout << lv << '\n';
                    K--;
                }
            }
            if(cur < L - 1 && not visited[next[1]]) {
                visited[next[1]] = true;
                q.emplace(next[1]);

                if(K > 0)
                {
                    cout << lv << '\n';
                    K--;
                }
            }
        }
        
        lv++;
    }

    return 0;
}
