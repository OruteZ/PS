#include<iostream>
#include<vector>
using namespace std;

#define MAX_SIZE (500)

int map[MAX_SIZE][MAX_SIZE] = {0, };
int n, m;
void input() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }
}

int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};

int memo[MAX_SIZE][MAX_SIZE] = {0,};
void memo_init() {
    for(auto &i : memo) {
        for(auto &j : i) {
            j = -1;
        }
    }
}

int calculate_path(int i, int j) {
    if(i == 0 and j == 0) return 1;
    if(memo[i][j] != -1) return memo[i][j];

    int result = 0;

    int next_i, next_j;
    for(int k = 0; k < 4; k++) {
        next_i = di[k] + i;
        next_j = dj[k] + j;

        if(next_i >= n or next_i < 0) continue;
        if(next_j >= m or next_j < 0) continue;
        if(map[next_i][next_j] <= map[i][j]) continue;

        result += calculate_path(next_i, next_j);
    }

    memo[i][j] = result;
    return result;
}

int main() {
    input();
    memo_init();
    cout << calculate_path(n - 1, m - 1) << endl;

    return 0;
}