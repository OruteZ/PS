#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>

#define MAX 1000
#define DEBUG false

#define LEFT 0
#define MIDDLE 1
#define RIGHT 2

typedef long long ll;

int route[MAX][MAX + 2];
int n, m;

int table[MAX + 1][MAX + 2][3] = {0,};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= m; j++) {
            std::cin >> route[i][j];
        }
        table[i][0][LEFT] = table[i][0][MIDDLE] = table[i][0][RIGHT] = route[i][0] = 1000 * 100;
        table[i][m + 1][LEFT] = table[i][m + 1][MIDDLE] = table[i][m + 1][RIGHT] = route[i][m+1] = 1000 * 100;
    }

    for(int j = 1; j <= m; j++) {
        table[0][j][LEFT] = table[0][j][MIDDLE] = table[0][j][RIGHT] = route[0][j];
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 1; j <= m; j++) {
            table[i + 1][j][LEFT] = std::min(table[i][j + 1][RIGHT], table[i][j + 1][MIDDLE]) + route[i + 1][j];
            table[i + 1][j][MIDDLE] = std::min(table[i][j][RIGHT], table[i][j][LEFT]) + route[i + 1][j];
            table[i + 1][j][RIGHT] = std::min(table[i][j - 1][LEFT], table[i][j - 1][MIDDLE]) + route[i + 1][j];
        }
    }

    if(DEBUG) {
        for(int i = 0; i < n; i++) {
            for(int j = 1; j <= m; j++) {
                std::cout << table[i][j][LEFT] << "," << table[i][j][MIDDLE] << "," << table[i][j][RIGHT] << " ";
            }
            std::cout << '\n';
        }
    }


    ll result = INT64_MAX;
    for(int j = 1; j <= m; j++) {
        int min = *std::min_element(table[n-1][j], table[n-1][j] + 3);
        result = min < result ? min : result;
    }

    std::cout << result;
}