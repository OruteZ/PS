#include <bits/stdc++.h>
using namespace std;

// sumAbs 를 delta[x] 변경 전후로 갱신하는 헬퍼
inline void applyDelta(int &sumAbs, int &dx, int deltaChange) {
    sumAbs -= abs(dx);
    dx += deltaChange;
    sumAbs += abs(dx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S; 
    int N;
    cin >> S;
    cin >> N;

    const int ALP = 26;
    int m = (int)S.size();

    // S의 빈도
    int base[ALP] = {0};
    for (char ch : S) base[ch - 'a']++;

    while (N--) {
        string T; 
        cin >> T;
        int L = (int)T.size();

        if (L < m) { 
            cout << "NO\n";
            continue;
        }

        // delta = windowCnt - base
        int delta[ALP];
        for (int i = 0; i < ALP; ++i) delta[i] = -base[i];

        int sumAbs = 0;
        for (int i = 0; i < ALP; ++i) sumAbs += abs(delta[i]);

        auto ok = [&](int sumAbsCur) -> bool {
            // 윈도우 바깥에서 치환: sumAbs == 0 && L > m
            if (sumAbsCur == 0 && L > m) return true;
            // 윈도우 안에서 치환: sumAbs == 2
            if (sumAbsCur == 2) return true;
            return false;
        };

        // 첫 윈도우 구성
        for (int i = 0; i < m; ++i) {
            int c = T[i] - 'a';
            applyDelta(sumAbs, delta[c], +1);
        }

        bool possible = ok(sumAbs);

        // 슬라이딩
        for (int i = m; !possible && i < L; ++i) {
            int inC  = T[i] - 'a';
            int outC = T[i - m] - 'a';
            applyDelta(sumAbs, delta[inC], +1);
            applyDelta(sumAbs, delta[outC], -1);
            if (ok(sumAbs)) {
                possible = true;
                break;
            }
        }

        // 주의: L == m 이고 sumAbs == 0 이면 치환이 없던 상태라 불가.
        if (!possible) {
            // 모든 윈도우가 sumAbs==0 이었고 L==m 인 특례는 이미 ok가 false라 걸리지 않음.
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
