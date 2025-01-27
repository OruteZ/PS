#include <bits/stdc++.h>
#define MOD 10007
#define MAX 1'000'000

using namespace std;
typedef long long ll;

int solve(int n) {
    if(n <= 2) return n;

    int threeCnt = n / 3;
    int twoCnt = 0;

    if (n % 3 == 1) {
        threeCnt--;
        twoCnt = 2;
    } else if (n % 3 == 2) {
        twoCnt = 1;
    }

    int answer = 1;
    for (int i = 0; i < threeCnt; i++) {
        answer *= 3;
        answer %= MOD;
    }

    for (int i = 0; i < twoCnt; i++) {
        answer *= 2;
        answer %= MOD;
    }

    return answer;
}

int main() {
    int n; cin >> n;

    cout << solve(n);
    return 0;
}