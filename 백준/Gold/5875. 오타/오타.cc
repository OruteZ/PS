#include <bits/stdc++.h>
using namespace std;

    //#define DEBUG

typedef long long int ll;

int toRight(const string &s) {
    vector<int> sum(s.size() + 1, 0);
    int close_cnt = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            sum[i + 1] = sum[i] + 1;
        } else {
            sum[i + 1] = sum[i] - 1;
            close_cnt++;
        }

        if (sum[i + 1] < 0) {
            return close_cnt;
        }
    }

    cout << "??" << endl;
    exit(1);
}

int toLeft(const string &s) {
    vector<int> sum(s.size() + 1, 0);
    int open_cnt = 0;

    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ')') {
            sum[i] = sum[i + 1] + 1;
        } else {
            sum[i] = sum[i + 1] - 1;
            open_cnt++;
        }

        if (sum[i] < 0) {
            return open_cnt;
        }
    }

    cout << "???" << endl;
    exit(1);
}

int main() {
    string s;

    cin >> s;

    int l_cnt = 0;
    int r_cnt = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            l_cnt++;
        } else {
            r_cnt++;
        }
    }

    
        if (l_cnt == r_cnt) {
            cout << 0 << endl;
            return 0;
        }
        
        if (l_cnt < r_cnt) {
            cout << toRight(s) << endl;
            return 0;
        } else {
            cout << toLeft(s) << endl;
            return 0;
        }
}