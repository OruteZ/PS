#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

vector<vector<int>> Max_table;
vector<vector<int>> Min_table;

vector<int> Numbers;
vector<char> Operators;

void init() {
    int size = Numbers.size();

    Max_table.assign(size + 1, vector<int>(size + 1, INT_MIN));
    Min_table.assign(size + 1, vector<int>(size + 1, INT_MAX));

    // DP 초기값 설정 (단일 숫자에 대한 경우)
    for (int i = 0; i < size; i++) {
        Max_table[i][i + 1] = Numbers[i];
        Min_table[i][i + 1] = Numbers[i];

        Max_table[i][i] = 0;
        Min_table[i][i] = 0;
    }
}

int solution(vector<string> arr) {
    // 숫자와 연산자 분리
    Numbers.clear(); Operators.clear();
    for(int i = 0; i < arr.size(); i++) {
        if (i % 2 == 0) {
            Numbers.push_back(stoi(arr[i]));
        } else {
            Operators.push_back(arr[i][0]);
        }
    }

    init();

    // DP 점화식 채우기
    for (int length = 2; length <= Numbers.size(); length++) {  // 부분 배열의 길이

        for (int begin = 0; begin <= Numbers.size() - length; begin++) {
            int end = begin + length;

            for (int mid = begin + 1; mid < end; mid++) {
                char op = Operators[mid - 1];

                if (op == '+') {
                    Max_table[begin][end] =
                            max(Max_table[begin][end], Max_table[begin][mid] + Max_table[mid][end]);
                    Min_table[begin][end] =
                            min(Min_table[begin][end], Min_table[begin][mid] + Min_table[mid][end]);
                }
                else { // -
                    Max_table[begin][end] = max(Max_table[begin][end], Max_table[begin][mid] - Min_table[mid][end]);
                    Min_table[begin][end] = min(Min_table[begin][end], Min_table[begin][mid] - Max_table[mid][end]);
                }

            }
        }
    }

    return Max_table[0][Numbers.size()];
}