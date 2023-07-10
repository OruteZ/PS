#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<random>
#include<cstring>
using namespace std;

typedef long long ll;
#define MAX 1'000'001

int k[MAX] = {0, };

void set_k(const char* P, int size) {
    int j = 0;

    for(int i = 1; i < size; i++) {
        while(j > 0 && P[i] != P[j]) {
            j = k[j - 1];
        }
        if (P[i] == P[j]) {
            k[i] = ++j;
        }
    }
}


int main() {
    char T[MAX];
    char P[MAX];

    cin.getline(T, MAX, '\n');
    cin.getline(P, MAX, '\n');

    int n = strlen(T);
    int m = strlen(P);

    set_k(P, m);

    int j = 0;
    int i = 0;
    vector<int> answers;

    while(i + j < n) {
        int cur = i + j;

        //cout << i << " " << j << " " << cur << '\n';
        if(T[cur] == P[j]) {
            if(j == m - 1) {
                answers.push_back(i + 1);
                if(cur == n - 1) break;
                i = cur - k[j - 1];
                j = k[j - 1];
            }
            else {
                j++;
            }
        }
        else {
            if(j == 0) i++;
            else {
                i = cur - k[j - 1];
                j = k[j - 1];
            }
        }
    }

//    for (int idx = 0; idx < m; idx++) { cout << k[idx] << " "; }
//    cout << endl;

    cout << answers.size() << '\n';
    for(int &ans : answers) cout << ans << " ";

    return 0;
}