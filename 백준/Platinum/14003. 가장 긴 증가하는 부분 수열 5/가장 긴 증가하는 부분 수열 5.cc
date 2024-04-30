#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>

#define INT_INF 2147483647
#define INT_NINF -2147483648
#define FASTIO std::ios_base::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
#define LL long long
#define PII std::pair<int, int>
#define ENDL '\n'
#define DEBUG true

int main() {
    FASTIO;

    int length;
    std::cin >> length;

    std::vector<int> arr(length);
    for(int i = 0; i < length; i++) {
        std::cin >> arr[i];
    }

    //---

    // combo[i] = arr[i]를 마지막 원소로 하는 LIS의 길이
    std::vector<int> combo(length);
    
    std::vector<int> dp = {arr[0]};

    for(int i = 1; i < length; i++) {
        auto it = std::lower_bound(dp.begin(), dp.end(), arr[i]);

        if(it != dp.end()) {
            *it = arr[i];

            int combo_stack = it - dp.begin();
            combo[i] = combo_stack;
        }
        else {
            dp.push_back(arr[i]);

            combo[i] = dp.size() - 1;
        }
    }

    std::cout << dp.size() << ENDL; 

    std::stack<int> result;

    int target = dp.size() - 1;
    for(auto it = combo.rbegin(); it != combo.rend(); it++) {
        if(*it == target) {
            int index = it - combo.rbegin();
            //reverse index
            index = combo.size() - index - 1;

            result.push(arr[index]);
            target--;
        }
    }

    while(!result.empty()) {
        std::cout << result.top() << " ";
        result.pop();
    }
    std::cout << ENDL;


    return 0;
}