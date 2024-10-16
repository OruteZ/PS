#include<bits/stdc++.h>

using namespace std;

inline void FAST_IO() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}


int getMinLength(vector<int>& arr, int target) {
	int left = 0; int right = 0;
	int sum = arr[0];

	int ret = INT_MAX;

	while(right < arr.size() and left <= right) {
		if(sum >= target) ret = min(ret, right - left + 1);

		if(sum < target) {
			if(right == arr.size() - 1) {
				break;
			}
			sum += arr[++right];
		}

		else {
			if(left == right) {
				break;
			}
			sum -= arr[left++];
		}
	}

	return ret == INT_MAX ? 0 : ret;
}

int main() {
	FAST_IO();
	
	int size; int target;
	cin >> size >> target;

	vector<int> arr(size);
	for(int& x : arr) cin >> x;

	cout << getMinLength(arr, target) << endl;
}