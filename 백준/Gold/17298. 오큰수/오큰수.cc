#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<array>
#include<algorithm>
#include<cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<int> arr(n);
    vector<int> answer(n);
    for(int &i : arr) {
        cin >> i;
    }

    stack<int> idx_stack;
    for(int i = 0; i < arr.size(); i++) {
        int cur = arr[i];
        while(not idx_stack.empty()) {
            int top = arr[idx_stack.top()];

            if(top < cur) {
                answer[idx_stack.top()] = cur;
                idx_stack.pop();
            }
            else break;
        }

        idx_stack.push(i);
    }

    while(not idx_stack.empty()) {
        answer[idx_stack.top()] = -1;
        idx_stack.pop();
    }

    for(int i : answer) cout << i << " ";


    return 0;
}

