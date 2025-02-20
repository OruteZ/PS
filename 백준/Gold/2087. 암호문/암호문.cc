#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, K;
vector<int> a;

// 주어진 배열의 모든 부분집합 합을 구하는 함수
vector<pair<int, int>> getSubsetSums(const vector<int>& arr) {
    int m = arr.size();
    vector<pair<int, int>> sums;  // (부분합, 비트마스크) 저장
    for (int mask = 0; mask < (1 << m); mask++) {
        int sum = 0;
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) sum += arr[i];
        }
        sums.emplace_back(sum, mask);
    }
    return sums;
}

// 비트마스크를 n-bit 문자열로 변환하는 함수
string maskToBitString(int mask, int size) {
    string bitStr = "";
    for (int i = 0; i < size; i++) {
        bitStr += (mask & (1 << i)) ? '1' : '0';
    }
    return bitStr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 입력 처리
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> K;

    // 절반으로 나누기
    int mid = n / 2;
    vector<int> left_part(a.begin(), a.begin() + mid);
    vector<int> right_part(a.begin() + mid, a.end());

    // 왼쪽, 오른쪽 부분합 계산
    vector<pair<int, int>> left_sums = getSubsetSums(left_part);
    vector<pair<int, int>> right_sums = getSubsetSums(right_part);

    // 오른쪽 부분합 정렬 (이진 탐색을 위해)
    sort(right_sums.begin(), right_sums.end());

    // Meet-in-the-Middle: 왼쪽 부분합을 순회하며 오른쪽에서 보완할 값 탐색
    for (auto& p : left_sums) {
        int left_sum = p.first;
        int left_mask = p.second;
        int target = K - left_sum;

        // 이진 탐색으로 target 찾기
        auto it = lower_bound(right_sums.begin(), right_sums.end(), make_pair(target, 0),
                              [](const pair<int, int>& a, const pair<int, int>& b) {
                                  return a.first < b.first;
                              });

        if (it != right_sums.end() && it->first == target) {
            int right_mask = it->second;
            cout << maskToBitString(left_mask, mid) + maskToBitString(right_mask, n - mid) << "\n";
            return 0;
        }
    }

    return 0;
}
