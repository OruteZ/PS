#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

vector<vector<int>> Max_table;
vector<vector<int>> Min_table;

vector<int> Numbers;
vector<char> Operators;

int dp_max(int begin, int end);
int dp_min(int begin, int end);

int dp_max(int begin, int end) {
    int& ret = Max_table[begin][end];
    if(ret != INT_MIN) return ret;

    for(int mid = begin + 1; mid < end; mid++) {
        char op = Operators[mid - 1];

        int left_max = dp_max(begin, mid);
        int right_max = dp_max(mid, end);
        int right_min = dp_min(mid, end);

        if(op == '+') ret = max(ret, left_max + right_max);
        else          ret = max(ret, left_max - right_min);
    }

    return ret;
}

int dp_min(int begin, int end) {
    int& ret = Min_table[begin][end];
    if(ret != INT_MAX) return ret;

    for(int mid = begin + 1; mid < end; mid++) {
        char op = Operators[mid - 1];

        int left_min = dp_min(begin, mid);
        int right_max = dp_max(mid, end);
        int right_min = dp_min(mid, end);

        if(op == '+') ret = min(ret, left_min + right_min);
        else          ret = min(ret, left_min - right_max);
    }

    return ret;
}

void init() {
    int size = Numbers.size();

    Max_table.assign(size + 1, vector<int>(size + 1, INT_MIN));
    Min_table.assign(size + 1, vector<int>(size + 1, INT_MAX));

    // DP 초기값 설정 (단일 숫자에 대한 경우)
    for (int i = 0; i < size; i++) {
        Max_table[i][i + 1] = Numbers[i];
        Min_table[i][i + 1] = Numbers[i];
    }
}

int solution(vector<string> arr) {
    // 숫자와 연산자 분리
    Numbers.clear(); 
    Operators.clear();
    for(int i = 0; i < arr.size(); i++) {
        if (i % 2 == 0) {
            Numbers.push_back(stoi(arr[i]));
        } else {
            Operators.push_back(arr[i][0]);
        }
    }

    init();

    return dp_max(0, Numbers.size());
}
