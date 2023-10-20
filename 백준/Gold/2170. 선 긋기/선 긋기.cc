#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#define DEBUG true
#define MAX 1'000'000

typedef std::pair<int, int> point;


std::vector<point> lines;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int size; std::cin >> size;

    for(int i = 0; i < size; i++) {
        int start, end;
        std::cin >> start >> end;

        lines.emplace_back(start, end);
    }


    std::sort(lines.begin(), lines.end());

    int result = 0;

    point cur_range(-INT32_MAX, -INT32_MAX);
    for(point& p : lines) {
        if(cur_range.second < p.first) {
            result += cur_range.second - cur_range.first;
            cur_range = p;
            continue;
        }

        cur_range.second = std::max(p.second, cur_range.second);
    }
    result += cur_range.second - cur_range.first;

    std::cout << result << '\n';
}