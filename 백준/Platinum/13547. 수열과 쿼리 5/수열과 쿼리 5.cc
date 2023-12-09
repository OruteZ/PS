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
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'

#define MAX 1'000'000
int cnt[MAX+1];
int answer = 0;

int block;

struct compare {
    bool operator() (const std::tuple<int, int, int> &left, const std::tuple<int, int, int> &right) const {
        int l_first = std::get<0>(left) / block;
        int l_second = std::get<1>(left);

        int r_first = std::get<0>(right) / block;
        int r_second = std::get<1>(right);

        //true = left 가 왼쪽 right가 오른쪽 가도록 정렬

        if(l_first != r_first) return l_first < r_first;

        if(l_first % 2 == 1) return l_second > r_second;
        else return l_second < r_second;
    }
};

void add(int key) {
    cnt[key]++;
    if(cnt[key] == 1) answer++;
}
void remove(int key) {
    cnt[key]--;
    if(cnt[key] == 0) answer--;
}

int main() {
    FAST_IO;

    int n; std::cin >> n;
    int array[n];
    for(int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    int m; std::cin >> m;

    int begin, end;
    std::vector<std::tuple<int, int, int>> q;

    int query_result[m];
    block = sqrt(m);

    for(int i = 0; i < m; i++) {
        std::cin >> begin >> end;
        begin--;

        q.emplace_back(begin, end, i);
    }
    std::sort(q.begin(), q.end(), compare());

//    if(DEBUG) for(int i = 0; i < q.size(); i++) {
//        std::cout << std::get<0>(q[i]) << ' ' << std::get<1>(q[i]) << ENDL;
//    }

    int l_ptr = 0, r_ptr = 0;
    for(auto &query : q) {
        while(l_ptr < std::get<0>(query)) remove(array[l_ptr++]);
        while(l_ptr > std::get<0>(query)) add(array[--l_ptr]);

        while(r_ptr < std::get<1>(query)) add(array[r_ptr++]);
        while(r_ptr > std::get<1>(query)) remove(array[--r_ptr]);

        query_result[std::get<2>(query)] = answer;
    }

    for(int i = 0; i < m; i++) {
        std::cout << query_result[i] << '\n';
    }
}