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

void init(vector<vector<string>>& route, int n) {
    route.resize(n);
    for(int i = 0; i < n; i++) {
        route[i].resize(n);
        for(string& value : route[i]) value = "";
    }
}

string str_max(string& a, string& b) {
    if(a.empty()) return b;
    if(b.empty()) return a;

    if(a.size() != b.size()) {
        return a.size() > b.size() ? a : b;
    }

    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) return a[i] > b[i] ? a : b;
    }

    return a;
}

void bfs(vector<vector<int>>& map, vector<vector<string>>& route) {
    pair<int, int> start = {0, 0};

    queue<pair<int, int>> container;
    container.push(start);

    int di[2] = {0, 1};
    int dj[2] = {1, 0};

    while(not container.empty()) {
        auto cur = container.front();
        container.pop();

        //next
        for(int d = 0; d < 2; d++) {
            pair<int, int> next = {cur.first + di[d], cur.second + dj[d]};
            if(next.first >= map.size() || next.second >= map.size()) continue;

            string& r = route[next.first][next.second];
            int v = map[next.first][next.second];
            string str = route[cur.first][cur.second] + to_string(v);

            r = str_max(r, str);

            container.push(next);
        }
    }
}

LL digit_to_int(string& str) {
    LL v = 1;
    LL ret = 0;
    for(auto riter = str.rbegin(); riter != str.rend(); riter++) {
        ret += (v) * (*riter == '1' ? 1 : 0);
        v *= 2;
    }

    return ret;
}


int main() {
    vector<vector<int>> map;
    vector<vector<string>> route;

    int n; cin >> n;

    input_map(map, n);
    init(route, n);
    route[0][0] = to_string(map[0][0]);

    bfs(map, route);

    cout << digit_to_int(route.back().back());
}
