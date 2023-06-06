#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


void solve() {
    string str1;
    string str2;

    cin >> str1 >> str2;
    if(str2.size() > str1.size()) swap(str1, str2);

    int length1 = str1.size();
    vector<int> lcs_vector(length1 + 1);
    vector<int> cache;
    for(auto &i : lcs_vector) i = 0;
    cache = lcs_vector;

    for(int i = 0; i < length1; i++) {
        if(str2.size() <= i) break;
        int max_val = cache[0];
        for(int j = 0; j < length1; j++) {
            bool is_same = (str2[i] == str1[j]);
            max_val = max(cache[j], max_val);
            if(is_same) {
                lcs_vector[j + 1] = max_val + 1;
            } else {
                lcs_vector[j + 1] = cache[j + 1];
            }
        }

//        for(int i = 1; i <= length1; i++) cout << lcs_vector[i] << " ";
//        cout << endl;

        cache = lcs_vector;
    }

    cout << *max_element(lcs_vector.begin(), lcs_vector.end()) << endl;
}

//-------------------------------------------- const code ------------------------------------------
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr); cout.tie(nullptr);
//
//    solve();
//
//    return 0;
//}
