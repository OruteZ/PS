#include<iostream>
using namespace std;

void solve() {
    int stk = 0;

    string input; cin >> input;
    for(auto c : input) {
        if(c == '(') stk++;
        else {
            if(stk == 0) {
                cout << "NO" << endl;
                return;
            }

            stk--;
        }
    }
    cout << (stk == 0 ? "YES" : "NO") << endl;
}

int main() {
    int n; cin >> n;

    while(n--) {
        solve();
    }
}

