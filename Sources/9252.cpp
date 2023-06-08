#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;


void solve() {
    string str1;
    string str2;

    cin >> str1 >> str2;
    str1 = ' ' + str1;
    str2 = ' ' + str2;
    if(str2.size() > str1.size()) swap(str1, str2);

    int len1 = str1.size();
    int len2 = str2.size();

    int lcs [len1][len2];
    for(int i = 0; i < len1; i++) for(int j = 0; j < len2; j++) lcs[i][j] = 0;

    for(int i = 1; i < len1; i++) {
        for(int j = 1; j < len2; j++) {
            if(str1[i] == str2[j]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    int r = len1 - 1;
    int c = len2 - 1;
    string answer;
    while(lcs[r][c] > 0) {
        if(lcs[r][c] == lcs[r][c-1]) c--;
        else if (lcs[r][c] == lcs[r-1][c]) r--;
        else {
            answer.push_back(str2[c]);
            c--; r--;
        }
    }

    reverse(answer.begin(), answer.end());

    cout << lcs[len1-1][len2-1] << endl;
    cout << answer << endl;
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
