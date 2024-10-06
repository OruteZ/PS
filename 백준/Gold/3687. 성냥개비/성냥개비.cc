#include<bits/stdc++.h>


#define LL long long int
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define IMPOSSIBLE -100

using namespace std;

int StickCost[10] = {6,2,5,5,4,5,6,3,7,6};
vector<vector<LL>> Dp;


void print_max(int n) {
    // 정답은 항상 n / 2자릿수의 숫자
    // n이 홀수일 경우, 7111... 형식
    // n이 짝수일 경우, 1111... 형식
    if(n % 2 == 0) {
        for(int i = 0; i < n / 2; i++) {
            cout << "1";
        }
    } else {
        cout << "7";
        for(int i = 0; i < n / 2 - 1; i++) {
            cout << "1";
        }
    }
}

// len 길이의 최소값을 구하는 함수
// -100을 리턴하면 불가능한 경우
LL get_min_num(int len, int n, bool is_first = false) {
	// base case : 1자리수
    if(len == 1) {
        for(int i = 0; i < 10; i++) {
            if(is_first and i == 0) continue;
            if(n - StickCost[i] == 0) {
                return i;
            }
        }

        return IMPOSSIBLE;
    }

	// base case : 2자리수 이면서 성냥개비 8개
    if(len == 2 and n == 8) {
        return 10;  
    }

	// ============== Memoization ==============

    LL& ret = Dp[len][n];
    if(ret != -1) return ret;

    ret = LLONG_MAX;
    for(int i = 0; i < 10; i++) {
        if(is_first and i == 0) continue;

        if(n - StickCost[i] >= 0) {
            LL next = get_min_num(len - 1, n - StickCost[i]);
            if(next == IMPOSSIBLE) continue;

            ret = min(ret, (LL)i * (LL)pow(10, len - 1) + next);
        }
    }

    if(ret == LLONG_MAX) ret = IMPOSSIBLE;
    return ret;
}

void print_min(int n) {
    int length = 0;
//    if(n <= 7) length = 1;
//    else {
//        length = n / 7;
//        if(n % 7 != 0) length++;
//    }


	length = n / 7;
	if(n % 7 != 0) length++;

    Dp.assign(length + 1, vector<LL>(n + 1, -1));

    LL ret = get_min_num(length, n, true);
    cout << ret;
}

void solution() {
    int n; 
    cin >> n;

    print_min(n);
    cout << " ";
    print_max(n);
    cout << "\n";
}

int main() {
    FASTIO;

    int t_case;
    cin >> t_case;

    while(t_case--) {
        solution();
    }

    return 0;
}