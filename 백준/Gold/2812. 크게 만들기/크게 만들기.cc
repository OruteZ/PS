#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

//--------------------------------------------------

void move(std::queue<int>& source, std::stack<int>& sink) {
    sink.push(source.front());
    source.pop();
}

void printStack(std::stack<int>& stk) {
    std::string ret = "";

    while(not stk.empty()) {
        ret.push_back(stk.top() + '0');
        stk.pop();
    }
    std::reverse(ret.begin(), ret.end());

    std::cout << ret << ENDL;
}

void debugStack(std::stack<int> stk) {
    std::string ret = "";

    while(not stk.empty()) {
        ret.push_back(stk.top() + '0');
        stk.pop();
    }
    std::reverse(ret.begin(), ret.end());

    std::cout << ret << ENDL;
}

void solve(std::queue<int>& origin, std::stack<int>& stk, int size) {
    while(true) {
        if(DEBUG) debugStack(stk);

        // 남은 숫자 다 들어 가야 하면
        if(origin.size() == size - stk.size()) {
            while(not origin.empty()) {
                move(origin, stk);
            }
            return;
        }
        if(origin.empty()) return;

        //case 1 : 빈곳에 넣기
        if(stk.empty()) {
            move(origin, stk);
            continue;
        }

        // case 2 : 더 클 때
        if (stk.top() < origin.front()) stk.pop();


        // case 3 : 작긴 한데 아직 빈자리 남았을 때
        else if (stk.size() < size) move(origin, stk);

        // case 4 : 빈자리도 없으면 그냥 pop
        else origin.pop();
    }
}

int main() {
    int total_length;
    int target_size;

    std::stack<int> stk;
    std::queue<int> origin;

    std::cin >> total_length >> target_size;
    std::string num;
    std::cin >> num;

    for(char s : num) {
        origin.push(s - '0');
    }

    solve(origin, stk, total_length - target_size);

    printStack(stk);
}