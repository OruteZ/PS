#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

void swap_range(int i, int j) {
    // swap the elements in the range A[i, j]
    for(int k = j; k > i; k--) {
        swap(A[k], A[k - 1]);
    }
}

int get_max(int start_idx, int length) {
    // return the index of the maximum element in the subarray A[start_idx, start_idx + length]
    int max_idx = start_idx;
    for (int i = start_idx + 1; i <= start_idx + length && i < N; i++) {
        if (A[i] > A[max_idx]) {
            max_idx = i;
        }
    }

    return max_idx;
}

int main() {
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    int total_swap_cnt = 0;
    cin >> total_swap_cnt;

    for(int i = 0; i < N; i++) {
        int max_idx = get_max(i, total_swap_cnt);
        int swap = max_idx - i;

        swap_range(i, max_idx);
        total_swap_cnt -= swap;
    }

    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
}