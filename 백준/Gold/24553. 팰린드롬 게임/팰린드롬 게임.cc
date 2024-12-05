#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        long long N;
        cin >> N;
        if(N % 10 == 0) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}
