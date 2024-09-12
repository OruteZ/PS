#include<bits/stdc++.h>

using namespace std;

// 5분 간격 사이 goal이 들어갈 확률 p
// 한 팀이 게임에서 n개의 골을 넣을 확률 : PerGoal(n) = Combination(18, n) * p^n * (1-p)^(18-n)
// 90분 경기에서 5분간격으로 구분하기 때문에, 가능한 소수 개수의 골 : 2, 3, 5, 7, 11, 13, 17
// 90분 동안 골이 들어올 확률 : PrimeGoal = PerGoal(2) + PerGoal(3) + PerGoal(5) + PerGoal(7) + PerGoal(11) + PerGoal(13) + PerGoal(17)
// 두 팀중 최소한 한 팀이 골을 넣을 확률 : AtLeastOneGoal = 1 - (1 - PrimeGoal)^2

int comb_cache[19][19] = {0, };
int primes[7] = {2, 3, 5, 7, 11, 13, 17};

int Combination(int n, int r) {
    if (r == 0 || n == r) return 1;
    if (comb_cache[n][r] != 0) return comb_cache[n][r];

    return comb_cache[n][r] = Combination(n-1, r-1) + Combination(n-1, r);
}

double PrimeGoal(double p) {
    double result = 0.0;

    for (int i = 0; i < 7; i++) {
        result += Combination(18, primes[i]) * pow(p, primes[i]) * pow(1-p, 18-primes[i]);
    }

    return result;
}




int main() {
    int team1, team2;

    cout << fixed;
    cout.precision(7);

    cin >> team1 >> team2;
    float rate1 = team1 / 100.0;
    float rate2 = team2 / 100.0;

    double p1 = PrimeGoal(rate1);
    double p2 = PrimeGoal(rate2);

    cout << 1 - (1 - p1) * (1 - p2) << endl;
}