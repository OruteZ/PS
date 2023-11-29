#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>

#define LL long long
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX 1000

std::vector<int> possible_works[MAX];

int person[MAX];
int works[MAX];

bool visited[MAX];

void clear_visited();

bool TryMatch(int p) {
    if(p == -1) return true;
    if(visited[p]) return false;
    visited[p] = true;

    for(int work : possible_works[p]) {
        if(TryMatch(works[work])) {
            person[p] = work;
            works[work] = p;
            return true;
        }
    }

    return false;
}

int main() {
    FAST_IO;
    int n, m;
    std::cin >> n >> m;

    for(int i = 0; i < MAX; i++) {
        person[i] = -1;
        works[i] = -1;
    }

    for(int i = 0; i < n; i++) {
        int cnt; std::cin >> cnt;
        REPEAT(cnt) {
            int w; std::cin >> w;
            w--;

            possible_works[i].push_back(w);
        }
    }

    int match_cnt = 0;
    for(int i = 0; i < n; i++) {
        if(person[i] != -1) continue;

        clear_visited();
        match_cnt += (int)TryMatch(i);
    }

    std::cout << match_cnt << std::endl;

    return 0;
}

void clear_visited() {
    for(int i = 0; i < MAX; i++) visited[i] = false;
}
