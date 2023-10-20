#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>

#define DEBUG true
#define MOD 1'000'000

typedef long long ll;

ll att[2][3] = {0,}; //L, A
ll att_before[2][3] = {0,};

void cur_to_before() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            att_before[i][j] = att[i][j];
            att[i][j] = 0;
        }
    }
}

void O() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            att[i][0] += att_before[i][j];
            att[i][0] %= MOD;
        }
    }
}

void L() {
    for(int a = 0; a < 3; a++) {
        att[1][0] += att_before[0][a];
        att[1][0] %= MOD;
    }
}

void A() {
    for(int l = 0; l < 2; l++) {
        for(int a = 0; a < 2; a++) {
            att[l][a + 1] += att_before[l][a];
            att[l][a + 1] %= MOD;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    n--;
    att[0][0] = 1;
    att[0][1] = 1;
    att[1][0] = 1;

    while(n--) {
        cur_to_before();

        O();
        L();
        A();
    }

    ll sum;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            sum += att[i][j];
        }
    }
    sum %= MOD;

    std::cout << sum;
}