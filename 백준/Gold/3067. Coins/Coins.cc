#include<bits/stdc++.h>

using namespace std;

void input(int& n, int& m, vector<int>& coins) {
    cin >> n;
    coins.resize(n);

    for(int& i : coins) cin >> i;

    cin >> m;
}

void solve() {
    int n, m;
    vector<int> coins;

    input(n, m, coins);

    vector<int> table(m + 1, 0);
    table[0] = 1; //아무것도 안내는 1가지 경우로 0원 완성 가능

    for(int coin : coins) {
        for(int target = coin; target <= m; target++) {
            table[target] += table[target - coin];
        }
    }

    cout << table[m] << endl;
}

int main() {
    int t_case;

    cin >> t_case;
    while(t_case--) {
        solve();
    }

    return 0;
}