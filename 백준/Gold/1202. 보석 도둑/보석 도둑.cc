#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

#define INT_INF 2147483647
#define FASTIO std::ios_base::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
#define LL long long
#define PII std::pair<int, int>

int main() {
    FASTIO;

// input
    int j_size, b_size;
    std::cin >> j_size >> b_size;

    std::vector<PII> jewels;
    std::vector<int> bags(b_size);
    
    for(int i = 0; i < j_size; i++) {
        int weight, value;
        std::cin >> weight >> value;
        jewels.emplace_back(weight, value);
    }

    for(int i = 0; i < b_size; i++) {
        std::cin >> bags[i];
    }

    sort(jewels.begin(), jewels.end());
    sort(bags.begin(), bags.end());


    //calculate
    LL result = 0;
    std::priority_queue<int> pq;
    int jewel_idx = 0;
    for(int bag : bags) {
        while(bag >= jewels[jewel_idx].first and jewel_idx < j_size) {
            pq.push(jewels[jewel_idx++].second);
        }

        if(not pq.empty()) {
            result += pq.top();
            pq.pop();
        }
    }

    std::cout << result << '\n';

    return 0;
}