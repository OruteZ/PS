#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int solution(vector<string> arr) {
    int n = arr.size();
    vector<int> nums;
    vector<char> ops;

    // 숫자와 연산자 분리
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            nums.push_back(stoi(arr[i]));
        } else {
            ops.push_back(arr[i][0]);
        }
    }

    int l = nums.size();
    // DP 테이블 초기화
    vector<vector<int>> max_dp(l, vector<int>(l, INT_MIN));
    vector<vector<int>> min_dp(l, vector<int>(l, INT_MAX));

    // DP 초기값 설정 (단일 숫자에 대한 경우)
    for (int i = 0; i < l; i++) {
        max_dp[i][i] = nums[i];
        min_dp[i][i] = nums[i];
    }

    // DP 점화식 채우기
    for (int length = 2; length <= l; length++) {  // 부분 배열의 길이
        for (int i = 0; i <= l - length; i++) {
            int j = i + length - 1;
            for (int k = i; k < j; k++) {
                if (ops[k] == '+') {
                    max_dp[i][j] = max(max_dp[i][j], max_dp[i][k] + max_dp[k+1][j]);
                    min_dp[i][j] = min(min_dp[i][j], min_dp[i][k] + min_dp[k+1][j]);
                } else if (ops[k] == '-') {
                    max_dp[i][j] = max(max_dp[i][j], max_dp[i][k] - min_dp[k+1][j]);
                    min_dp[i][j] = min(min_dp[i][j], min_dp[i][k] - max_dp[k+1][j]);
                }
            }
        }
    }

    return max_dp[0][l-1];
}

int main() {
    vector<string> arr1 = {"1", "-", "3", "+", "5", "-", "8"};
    vector<string> arr2 = {"5", "-", "3", "+", "1", "+", "2", "-", "4"};

    cout << solution(arr1) << endl;  // 결과: 1
    cout << solution(arr2) << endl;  // 결과: 3

    return 0;
}
