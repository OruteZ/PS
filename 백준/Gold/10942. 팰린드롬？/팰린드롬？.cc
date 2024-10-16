#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

int N, M, S, E;

int array[2001];
char DP[2001][2001] = {0,};

bool palindrome(int i, int j) {
    if(i >= j) return true;

    if(DP[i][j] != 0){
        if(DP[i][j] == 1) return true;
        else return false;
    }

    else {
        if(array[i] != array[j]){
            DP[i][j] = -1;
        } else if (palindrome(i+1, j-1)){
            DP[i][j] = 1;
        } else {
            DP[i][j] = -1;
        }

        if(DP[i][j] == 1) return true;
        else return false;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);std::cout.tie(nullptr);

    cin >> N;

    for(int i = 1; i <= N; i++){
        cin >> array[i];
    }

    cin >> M;
    while(M--){
        cin >> S >> E;
        cout << palindrome(S, E) << "\n";
    }

    return 0;
}
