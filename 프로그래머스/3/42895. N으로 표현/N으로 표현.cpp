#include <vector>
#include <unordered_set>

using namespace std;

// DP[i] = i번의 N으로 반들어 낼 수 있는 수의 집합
vector< unordered_set<int> > DP(8);

int get_concat_N(int N, int idx) {
    int result = N;
    for (int i = 1; i <= idx; i++) {
        result = result * 10 + N;
    }

    return result;
}

int solution(int N, int number) {
    if (N == number) return 1;

    DP[0].insert(N);

    for (int k = 1; k < 8; k++) {
        DP[k].insert(get_concat_N(N, k));

        for (int i = 0; i < k; i++) {
            int j = k - i - 1; 
            for (int a : DP[i]) {
                for (int b : DP[j]) {

                    // 사칙연산
                    DP[k].insert(a + b);
                    if (a - b > 0) DP[k].insert(a - b);
                    DP[k].insert(a * b);
                    if (a / b > 0) DP[k].insert(a / b);
                }
            }
        }

        if (DP[k].find(number)!=DP[k].end())
            return k + 1;
    }
    return -1;
}