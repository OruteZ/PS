#include <iostream>
#include <algorithm>
using namespace std;

bool can_change(const string& source, string target) {
    if (source.size() == target.size()) {
        return source == target;
    }

    if (target.back() == 'A') {
        target.pop_back();
        return can_change(source, target);
    } else {
        target.pop_back();
        reverse(target.begin(), target.end());
        return can_change(source, target);
    }
}

int main() {
    string S, T;
    cin >> S >> T;
    
    cout << (int)can_change(S, T) << endl;
    
    return 0;
}