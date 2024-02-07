#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

int map[64][64];

string ZIP(int i, int j, int size) {

    //base case + 다 똑같을 때
    int first_color = map[i][j];
    bool all_color_same_flag = true;
    for(int next_i = i; next_i < i + size; next_i++) {
        for(int next_j = j; next_j < j + size; next_j++) {
            if(map[next_i][next_j] != first_color) {
                all_color_same_flag = false;
                break;
            }
        }
        if(!all_color_same_flag) break;
    }
    if(all_color_same_flag) return to_string(first_color);


    //else : 분할
    string result = "";
    size /= 2;

    result = ZIP(i, j, size);
    result += ZIP(i, j + size, size);
    result += ZIP(i +size, j , size);
    result += ZIP (i + size, j + size, size);

    return "(" + result + ")";
}

int main() {
    FAST_IO

    int size; cin >> size;

    for(int i = 0; i < size; i++) {
        string input;
        cin >> input;
        for(int j = 0; j < size; j++) {
            map[i][j] = input[j] - '0';
        }
    }

    cout << ZIP(0, 0, size);
}
