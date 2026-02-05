#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    const int OFF = 200000;          // [-200000, 200000] 범위를 배열 인덱스 [0, 400000]으로 옮기기 위한 오프셋
    const int MAXI = 400000;

    // possible[합 + OFF] = (지금까지 나온 수들 중 "두 수의 합"으로 해당 값이 만들어질 수 있으면 1)
    vector<char> possible(MAXI + 1, 0);

    int ans = 0;

    for (int i = 0; i < N; i++) {
        bool good = false;

        // A[i]가 좋은 수인지 판정:
        // A[x] + A[y] + A[j] = A[i]  (x,y,j < i)
        // <=> A[x] + A[y] = A[i] - A[j]
        // 즉, (A[i] - A[j])가 "이전에 만들 수 있었던 두 수의 합"인지 확인하면 된다.
        for (int j = 0; j < i; j++) {
            int need = A[i] - A[j];      // 필요로 하는 두 수의 합 값
            int idx = need + OFF;
            if (0 <= idx && idx <= MAXI && possible[idx]) {
                good = true;
                break;
            }
        }

        if (good) ans++;

        // 다음 원소들을 위해 "두 수의 합" 테이블 업데이트:
        // i번째 수 A[i]를 사용해서 A[i] + A[j] (j <= i) 를 전부 표시한다.
        // (문제에서 같은 수를 여러 번 써도 되므로 j == i 도 포함해서 A[i] + A[i]도 가능)
        for (int j = 0; j <= i; j++) {
            int s = A[i] + A[j];
            possible[s + OFF] = 1;       // 해당 합은 만들 수 있다고 체크
        }
    }

    cout << ans << "\n";
    return 0;
}
