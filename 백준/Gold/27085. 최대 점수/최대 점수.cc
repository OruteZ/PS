#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, s;
ll maxScore = 0;
vector<ll> dungeon;

// 오른쪽으로 가능한 만큼 확장하고 마지막 위치를 반환
int moveRight(int cursor, ll beforeMax) {
    if (cursor >= N - 1) return cursor;
    // 현재까지의 maxScore 변화분을 더해 시작 버퍼 계산
    ll v = maxScore - beforeMax + dungeon[cursor];
    cursor++;
    while (cursor < N) {
        if (v + dungeon[cursor] < 0) {
            return cursor - 1;
        }
        // 누적 버퍼를 dungeon에 합쳐서 다음 단계에 사용
        dungeon[cursor] += v;
        v = dungeon[cursor];
        maxScore = max(maxScore, v);
        cursor++;
    }
    return N - 1;
}

// 왼쪽으로 가능한 만큼 확장하고 마지막 위치를 반환
int moveLeft(int cursor, ll beforeMax) {
    if (cursor <= 0) return cursor;
    ll v = maxScore - beforeMax + dungeon[cursor];
    cursor--;
    while (cursor >= 0) {
        if (v + dungeon[cursor] < 0) {
            return cursor + 1;
        }
        dungeon[cursor] += v;
        v = dungeon[cursor];
        maxScore = max(maxScore, v);
        cursor--;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> s;
    dungeon.resize(N);
    for (int i = 0; i < N; i++) cin >> dungeon[i];

    int lCursor = s - 1, rCursor = s - 1;
    ll lBeforeMax = 0, rBeforeMax = 0;
    maxScore = 0;

    while (true) {
        // 오른쪽 확장
        rCursor = moveRight(rCursor, rBeforeMax);
        rBeforeMax = maxScore;
        // 왼쪽 확장
        lCursor = moveLeft(lCursor, lBeforeMax);
        lBeforeMax = maxScore;
        // 오른쪽 확장 시 maxScore가 변하지 않았다면 더 이상 늘릴 수 없음
        if (maxScore == rBeforeMax) break;
    }

    cout << maxScore;
    return 0;
}
