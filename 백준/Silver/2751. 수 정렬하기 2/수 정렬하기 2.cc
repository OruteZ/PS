#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;

    vector<int> nums(N);

    for(int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());

    for(int i : nums) {
        cout << i << "\n";
    }
}