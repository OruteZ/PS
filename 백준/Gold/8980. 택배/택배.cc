#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

struct info {
    int start;
    int dest;
    int cnt;

    int dist;
    bool visited;
    void set(int s, int d, int c) {
        start = s;
        dest = d;
        cnt = c;

        dist = dest - start;
        visited = false;
    }
};

struct comp_dest {
    bool operator() (const info& down, const info& top) {
        return down.dest < top.dest;
    }
};

void clamp(int& value, int min, int max) {
    if(min > max) exit(-190);

    if(value > max) value = max;
    if(value < min) value = min;
}

void print_vec(std::vector<int>& v) {
    PRINT_LINE;
    for(int i : v) std::cout << i << ' ';
    std::cout << ENDL;
    PRINT_LINE;
}

int main() {
    int town_size, truck_capacity, info_size;
    std::cin >> town_size >> truck_capacity >> info_size;

    std::vector<info> info_list(info_size);
    int s, d, c;
    for(info& i : info_list) {
        std::cin >> s >> d >> c;
        i.set(s, d, c);
    }
    std::sort(info_list.begin(), info_list.end(), comp_dest());

    if(DEBUG) {
        for(info i : info_list) {
            std::cout << i.start << ' ' << i.dest << ' ' << i.cnt << ENDL;
        } std::cout << ENDL;
    }

    std::vector<int> trucks(town_size + 1);

    int answer = 0;
    for(info& i : info_list) {
        auto start = trucks.begin() + i.start;
        auto end = trucks.begin() + i.dest;

        int max_cap = *std::max_element(start, end);
        int spare_cap = truck_capacity - max_cap;

        int target_cap = i.cnt;
        clamp(target_cap, 0, spare_cap);

        answer += target_cap;
        std::for_each(start, end, [target_cap](auto& iter){iter += target_cap;});

        if(DEBUG) print_vec(trucks);
    }

    std::cout << answer;
}