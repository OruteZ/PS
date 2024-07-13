#include <bits/stdc++.h>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 1e4
#define INT_M_INF (-2147483648)

using namespace std;
//-----------------------------

int N, M;
vector<vector<int>> city_info;
vector<PII> houses;
vector<PII> chickens;
int Answer = INT_INF;

int get_dist(const PII& a, const PII& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void setup() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            if(city_info[i][j] == 2) chickens.emplace_back(i, j);
            if(city_info[i][j] == 1) houses.emplace_back(i, j);

        }
    }
}

int get_chicken_dist(PII& house, const vector<PII>& selected_chickens) {
    int ret = INT_INF;
    for(const PII& c : selected_chickens) {
        ret = min(ret, get_dist(house, c));
    }

    return ret;
}

void check_answer(const vector<PII>& result) {
    if(DEBUG) {
        cout << "Check answer call : \n ";
        for(auto& i : result) cout << i.first << ',' << i.second << ' ';
        cout << ENDL;
    }

    int answer = 0;
    for(auto& house : houses) {
        answer += get_chicken_dist(house, result);
        if(DEBUG) cout << " answer : " << answer << ENDL;
    }

    Answer = min(answer,  Answer);
}

void select_chicken(vector<PII>& result, int idx, bool is_start = false) {
    if(is_start) {
        result.clear();
        idx = 0;
    }

    if(result.size() == M || idx == chickens.size()) {
        check_answer(result);
        return;
    }

    result.push_back(chickens[idx]);
    select_chicken(result, idx + 1);
    result.pop_back();
    select_chicken(result, idx + 1);
}

int main() {
    // 치킨 M개를 골라서 (C(13, M))
    //

    cin >> N >> M;
    city_info.assign(N, vector<int>(N));

    for(auto& line : city_info) {
        for(int& i : line) {
            cin >> i;
        }
    }

    setup();

    vector<PII> container;
    select_chicken(container, 0, true);

    cout << Answer << endl;

    return 0;
}
