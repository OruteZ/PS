#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>
#include<map>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)


using namespace std;

void input_map(vector<vector<int>>& map, int n) {
    map.resize(n);
    for(int i = 0; i < n; i++) {
        map[i].resize(n);
        for(int& value : map[i]) cin >> value;
    }
}

void init(vector<vector<LL>>& route, int n) {
    route.resize(n);
    for(int i = 0; i < n; i++) {
        route[i].resize(n);
        for(LL& value : route[i]) value = 0;
    }
}

void tabulation(vector<vector<int>>& map, vector<vector<LL>>& route) {
    int size = map.size();
    auto get_value = [&size, &route](int i, int j)->LL {
        if(i < 0 || i >= size) return -1;
        if(j < 0 || j >= size) return -1;

        return route[i][j];
    };

    for(int lv = 1; lv <= (size - 1) * 2; lv++) {
        for(int i = 0; i <= lv; i++) {
            int j = lv - i;

            if(i >= size) continue;
            if(j >= size) continue;
            if(i < 0) continue;
            if(j < 0) continue;

            LL before_max = max(get_value(i - 1, j), get_value(i, j - 1));
            route[i][j] = before_max * 2 + map[i][j];
        }

//        for(int i = 0; i < size; i++) {
//            for(int j = 0; j < size; j++) {
//                cout << route[i][j] << ' ';
//            } cout << ENDL;
//        } cout << ENDL;
    }
}


int main() {
    vector<vector<int>> map;
    vector<vector<LL>> route;

    int n; cin >> n;

    input_map(map, n);
    init(route, n);
    route[0][0] = map[0][0];

    tabulation(map, route);

    cout << (route.back().back());
}
