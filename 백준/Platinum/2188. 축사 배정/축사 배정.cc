#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 201;  // 최대 소의 수 및 축사의 수

vector<int> cow_wishes[MAX_N];  // 소가 원하는 축사 목록
int matched[MAX_N];             // 매칭된 축사 정보
bool visited[MAX_N];            // DFS 방문 여부

bool dfs(int cow) {
    for (int barn : cow_wishes[cow]) {
        if (visited[barn]) continue;
        visited[barn] = true;

        // 축사가 비어있거나, 기존의 매칭된 소를 다른 곳으로 이동 가능하면 매칭
        if (matched[barn] == -1 || dfs(matched[barn])) {
            matched[barn] = cow;
            return true;
        }
    }

    return false;
}

int max_matching(int n) {
    int result = 0;
    memset(matched, -1, sizeof(matched));  // 매칭 초기화

    for (int cow = 1; cow <= n; cow++) {
        memset(visited, false, sizeof(visited));  // 방문 초기화
        if (dfs(cow)) {
            result++;
        }
    }

    return result;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int si;
        cin >> si;
        for (int j = 0; j < si; j++) {
            int barn;
            cin >> barn;
            cow_wishes[i].push_back(barn);
        }
    }

    cout << max_matching(n) << endl;

    return 0;
}
