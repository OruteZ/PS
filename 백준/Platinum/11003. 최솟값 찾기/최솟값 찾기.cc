#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>
#include<deque>

#define INT_INF 2147483647
#define INT_NINF -2147483648
#define FASTIO std::ios_base::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
#define LL long long
#define PII std::pair<int, int>
#define ENDL '\n'
#define DEBUG true

void push_in_window(std::deque<int> &window, int value) {
    while(!window.empty() && window.back() > value) {
        window.pop_back();
    }
    window.push_back(value);
}

int main() {
    FASTIO;

    int arr_size, window_size;
    std::cin >> arr_size >> window_size;

    std::vector<int> arr(arr_size);
    for(int i = 0; i < arr_size; i++) {
        std::cin >> arr[i];
    }

    std::deque<int> window;
    for(int i = 0; i < arr_size; i++) {
        push_in_window(window, arr[i]);

        int pop_index = i - window_size;
        if(pop_index >= 0) {
            if(arr[pop_index] == window.front()) {
                window.pop_front();
            }
        }

        

        std::cout << window.front() << " ";
    }
    




    return 0;
}