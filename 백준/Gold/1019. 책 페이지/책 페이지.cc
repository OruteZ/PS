#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>

#pragma region MACRO

#define LL long long
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)

#pragma endregion

std::array<LL, 10> answer;

void calc(int number, int multiplier) {
    if(number == 0) answer[0] += multiplier;
    while(number > 0) {
        answer[number % 10] += multiplier;
        number /= 10;
    }

    if(DEBUG) {
        for(int i = 0; i < 10; i++) std::cout << answer[i] << " " ;
        std::cout << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int start, last;

    start = 1;
    std::cin >> last;

    int multiplier = 1;

    while(start <= last) {
        while(start % 10 != 0) {

            if(start > last) goto FINISH;
            calc(start++, multiplier);
        }

        while(last % 10 != 9) {
            calc(last--, multiplier);
            if(start > last) goto FINISH;
        }


        LL cnt = last / 10 - start / 10 + 1;
        for(int i = 0; i < 10; i++) answer[i] += cnt * multiplier;

        multiplier *= 10;
        start /= 10;
        last /= 10;
    }

    FINISH:
    for(int i = 0; i < 10; i++) std::cout << answer[i] << " " ;

    return 0;
}