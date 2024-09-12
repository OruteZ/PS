#include <bits/stdc++.h>

using namespace std;


// ================== 변수 정의 ==================
#define MAX 20
#define DEBUG false

int N;
bitset<MAX> Board[MAX];
bitset<MAX> Backup[MAX];

// answer 관련
int ZeroCount = 987654321;

// ================== 함수 정의 (After BackTracking) ==================

void PrintBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << Board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void FlipCol(int col) {
    for (int i = 0; i < N; i++) {
        Board[i].flip(col);
    }
}

int CountZero(int col) {
    int zeroCount = 0;
    for (int i = 0; i < N; i++) {
        zeroCount += Board[i][col] == 0;
    }

    return zeroCount;
}

// 각 행을 뒤집은 이후에, 열을 Greedy 하게 뒤집는다.
// 이후 총 뒤집은 횟수와 뒷면의 개수를 계산해서 정답 갱신
void FindAnswer() {
    int zeroCount = 0;

    for(int col = 0; col < N; col++) {
        int cnt = CountZero(col);
        if (cnt > N - cnt) {
            FlipCol(col);
        }

        // fliped ? N - cnt : cnt
        zeroCount += min(cnt, N - cnt);
    }

    if (zeroCount < ZeroCount) {
        ZeroCount = zeroCount;
    }

    if (DEBUG) {
        PrintBoard();
    }
}


// ================== 함수 정의 (BackTracking) ==================

void Recursion(stack<bool>& flipCase) {
    if (flipCase.size() == N) {
        // do flip
        stack<bool> temp = flipCase;

        for (int i = 0; i < N; i++) {
            if (temp.top()) {
                Board[i].flip();
            }
            temp.pop();
        }
        FindAnswer();

        
        // set board to backup
        for (int i = 0; i < N; i++) {
            Board[i] = Backup[i];
        }

        return;
    }

    flipCase.push(false);
    Recursion(flipCase);
    flipCase.pop();

    flipCase.push(true);
    Recursion(flipCase);
    flipCase.pop();
}

void Init() {
    cin >> N;

    char c;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> c;

            Board[i][j] = c == 'H';
            Backup[i][j] = Board[i][j];
        }
    }

    
}

int main() {
    Init();

    stack<bool> flipCase;

    Recursion(flipCase);

    cout << ZeroCount << endl;

    return 0;
}