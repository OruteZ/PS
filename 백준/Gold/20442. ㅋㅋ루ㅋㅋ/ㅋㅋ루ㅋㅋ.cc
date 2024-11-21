#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.length();
    vector<int> left_k_cnt(n, 0), right_k_cnt(n, 0);
    vector<int> r_positions;

    // 왼쪽 K의 개수를 세는 배열 생성
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            left_k_cnt[i] = left_k_cnt[i - 1];
        }
        if (s[i] == 'K') {
            left_k_cnt[i]++;
        }
    }

    // 오른쪽 K의 개수를 세는 배열 생성
    for (int i = n - 1; i >= 0; --i) {
        if (i < n - 1) {
            right_k_cnt[i] = right_k_cnt[i + 1];
        }
        if (s[i] == 'K') {
            right_k_cnt[i]++;
        }
    }

    // R의 위치를 저장
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'R') {
            r_positions.push_back(i);
        }
    }

    // 투 포인터를 이용해 가장 긴 "ㅋㅋ루ㅋㅋ"의 길이를 계산
    int left = 0, right = r_positions.size() - 1;
    int max_length = 0;

    while (left <= right) {
        int l = r_positions[left]; // 왼쪽 R의 위치
        int r = r_positions[right]; // 오른쪽 R의 위치

        // R의 개수 + 양쪽 K 중 작은 값 * 2
        int current_length = (right - left + 1) + 2 * min(left_k_cnt[l], right_k_cnt[r]);
        max_length = max(max_length, current_length);

        // 왼쪽 K와 오른쪽 K의 개수를 비교하여 포인터 이동
        if (left_k_cnt[l] < right_k_cnt[r]) {
            left++;
        } else {
            right--;
        }
    }

    cout << max_length << endl;

    return 0;
}
