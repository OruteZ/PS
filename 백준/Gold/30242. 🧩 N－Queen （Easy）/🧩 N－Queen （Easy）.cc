#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> Q;

void print_queens() {
    for(int& pos : Q) cout << pos << ' ';
}

bool col_available(int col) {
    return find(Q.begin(), Q.end(), col) == Q.end();
}

bool diagonal_available(int col, int row) {
    auto diagonal_link = [col, row](int t_col, int t_row) {
        if(t_col == 0) return false;

        return abs(col - t_col) == abs(row - t_row) ;
    };

    // idx == row
    for(int t_row = 1; t_row <= N; t_row++) {
        if(t_row == row) continue;

        int t_col = Q[t_row - 1];
        bool d_link = diagonal_link(t_col, t_row);
        if(d_link) return false;
    }

    return true;
}

bool find(int cur_row) {
    if(cur_row == N + 1) {
        print_queens();
        return true;
    }

    if(Q[cur_row - 1] != 0) {
        return find(cur_row + 1);
    }

    for(int i = 1; i <= N; i++) {
        bool is_available =
                col_available(i) &&
                diagonal_available(i, cur_row);

        if(is_available) {
            Q[cur_row - 1] = i;

            bool result = find(cur_row + 1);
            if(result) return true;

            Q[cur_row - 1] = 0;
        }
    }

    return false;
}

int main() {
    cin >> N;
    Q.resize(N, 0);
    for(int& pos : Q) cin >> pos;

    bool result = find(1);
    if(not result) {
        cout << -1;
    }

    return 0;
}
