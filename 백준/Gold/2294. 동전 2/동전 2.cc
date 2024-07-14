#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

typedef long long ll;

const int INF = 2000000000;

ll table[101][10001] = {0,};

int coin[101];

void printTable(int n, int k) {
    cout << "----------------" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            cout << table[i][j] << " ";
        } cout << endl;
    } cout << "----------------" << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);std::cout.tie(nullptr);

    int n; cin >> n;
    int k; cin >> k;
    for(int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    for(int j = 1; j <= k; j++) {
        if(j % coin[0] == 0) {
            table[0][j] = j / coin[0];
        }
        else table[0][j] = INF;
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= k; j++) {
            if(coin[i] > j) {
                table[i][j] = table[i-1][j];
            }
            else {
                ll val1 = table[i][j - coin[i]] + 1;
                ll val2 = table[i-1][j];

                table[i][j] = val1 < val2 ? val1 : val2;
            }
        }
    }

   // printTable(n,k);

    if(table[n-1][k] < INF) cout << table[n-1][k];
    else cout << -1;


    return 0;
}
