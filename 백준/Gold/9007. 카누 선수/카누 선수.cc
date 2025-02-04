#include<bits/stdc++.h>
using namespace std;

#define DEBUG false

inline int getCloser(int a, int b, int target) {
    int val_a = abs(a - target);
    int val_b = abs(b - target);

    if(val_a == val_b) {
        return min(a, b);
    }

    return val_a < val_b ? a : b;
}

int solve(int n, int k, const vector<vector<int>>& weights) {
    vector<int> sum1(n*n, 0);
    vector<int> sum2(n*n, 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sum1[i*n + j] = weights[0][i] + weights[1][j];
            sum2[i*n + j] = weights[2][i] + weights[3][j];
        }
    }

    // 캐시 적중률 향상을 위해 정렬
    sort(sum1.begin(), sum1.end());
    sort(sum2.begin(), sum2.end());


    // 이분탐색으로 sum[i] + sum[j] 중 target과 가장 가까운 값을 찾는다.
    // 거리가 같은 경우 더 작은 값을 선택한다.
    int answer = -4e8;
    for(int first : sum1) {
        int target = k - first;
        auto it = lower_bound(sum2.begin(), sum2.end(), target);

        if(it == sum2.begin()) {
            answer = getCloser(answer, first + *it, k);
            continue;
        }

        // 찾았을 경우
        if(it != sum2.end()) {
            int over = *it;
            int under = *(--it);

            answer = getCloser(answer, first + over, k);
            answer = getCloser(answer, first + under, k);
        } else {
            answer = getCloser(answer, first + *(it - 1), k);
        }
    }

    return answer;
}


int main() {
    int t_case;
    cin >> t_case;

    vector<vector<int>> weights(4);
    int target;

    while(t_case--) {

        if(DEBUG) cout << endl << "Case " << t_case << endl;

        int n, k;
        cin >> k >> n;

        if(DEBUG) cout << "n: " << n << " k: " << k << endl;

        for(int i = 0; i < 4; i++) {
            weights[i].clear();
            for (int j = 0; j < n; j++) {
                int w;
                cin >> w;
                weights[i].push_back(w);
            }
        }

        if(DEBUG) {
            for(int i = 0; i < 4; i++) {
                for (int j = 0; j < n; j++) {
                    cout << weights[i][j] << " ";
                }
                cout << endl;
            }
        }

        cout << solve(n, k, weights) << endl;
    }
    
}