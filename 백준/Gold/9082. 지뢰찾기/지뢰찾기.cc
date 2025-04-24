#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        string top, bot;
        cin >> top >> bot;

        int best = 0;
        // x[i] = 0 or 1 으로 bottom[i]의 지뢰 여부
        // 첫 칸 x0 는 bot[0]=='*' 이면 1 고정, 아니면 0 또는 1 두 가지 시도
        for (int init = 0; init <= 1; init++) {
            if (bot[0] == '*' and init == 0) continue;
            if (bot[0] == '#' and init > 1) continue; // 의미 없지만 안전장치

            vector<int> x(N, 0);
            bool ok = true;
            x[0] = init;

            // N==1 특수 처리
            if (N == 1) {
                // 위 숫자 == x0 이어야 함
                if (x[0] != top[0] - '0') ok = false;
                if (ok) best = max(best, x[0]);
                continue;
            }

            // i=0 에서 x1 계산
            x[1] = (top[0] - '0') - x[0];
            if (x[1] < 0 || x[1] > 1) ok = false;
            if (bot[1] == '*' and x[1] != 1) ok = false;

            // i=1..N-2 에서 차례로 전파
            for (int i = 1; ok && i <= N-2; i++) {
                // i 위치 처리는 이미 x[i] 알고 있고, 이제 x[i+1] 계산
                int need = (top[i] - '0') - x[i-1] - x[i];
                if (need < 0 or need > 1) { ok = false; break; }
                x[i+1] = need;
                if (bot[i+1] == '*' and x[i+1] != 1) { ok = false; break; }
            }
            if (!ok) continue;

            // 마지막 열 N-1 의 숫자 제약 확인: x[N-2] + x[N-1] == top[N-1]
            if (x[N-2] + x[N-1] != top[N-1] - '0') continue;

            // 유효 배치이면 지뢰 개수 집계
            int cnt = 0;
            for (int v : x) cnt += v;
            best = max(best, cnt);
        }

        cout << best << "\n";
    }
    return 0;
}
