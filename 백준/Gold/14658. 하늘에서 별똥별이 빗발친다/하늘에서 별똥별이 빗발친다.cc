#include <bits/stdc++.h>

using namespace std;

int MapX;
int MapY;

int Length;
int StarCount;

struct Pos {
    int x;
    int y;
};

vector<Pos> StarPos;

bool IsIntersect(Pos left_top, Pos right_bottom, Pos star) {
    if(star.x < left_top.x || star.x > right_bottom.x) {
        return false;
    }

    if(star.y > left_top.y || star.y < right_bottom.y) {
        return false;
    }

    return true;
}

int CountFallingStar(Pos left_top) {
    Pos right_bottom;
    right_bottom.x = left_top.x + Length;
    right_bottom.y = left_top.y - Length;

    int count = 0;
    for (int i = 0; i < StarCount; i++) {
        if (IsIntersect(left_top, right_bottom, StarPos[i])) {
            count++;
        }
    }
    return StarCount - count;
}

int main() {
    cin >> MapX >> MapY >> Length >> StarCount;

    for (int i = 0; i < StarCount; i++) {
        Pos pos;
        cin >> pos.x >> pos.y;
        StarPos.push_back(pos);
    }

    int result = 987654321;
    Pos result_pos;
    
    for(Pos& starA : StarPos) {
        for(Pos& starB : StarPos) {
            Pos left_top;
            left_top.x = min(starA.x, starB.x);
            left_top.y = max(starA.y, starB.y);

            int count = CountFallingStar(left_top);
            if(result > count) {
                result = count;
                result_pos = left_top;
            }
        }
    }

    // cout << "final" << endl;
    cout << result << endl;
    // cout << result_pos.x << " " << result_pos.y << endl;

    return 0;
}