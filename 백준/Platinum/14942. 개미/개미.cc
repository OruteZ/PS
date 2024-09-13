#include <bits/stdc++.h>

using namespace std;

#define LL long long int
#define MAX_ROOM 100'000
#define DEBUG 0

int RoomCnt;
int AntEnergy[MAX_ROOM + 1];
vector<vector<pair<int, int>>> AdjList(MAX_ROOM + 1);

// 희소 배열
vector<vector<int>> SparseTable(20, vector<int>(MAX_ROOM + 1));
vector<vector<int>> SparseCostTable(20, vector<int>(MAX_ROOM + 1));

// DEBUG
void PrintSparseTable() {
    for (int i = 0; i < 20; i++) {
        for (int j = 1; j <= RoomCnt; j++) {
            cout << SparseTable[i][j] << " ";
        }
        cout << endl;
    }
}

void PrintSparseCostTable() {
    for (int i = 0; i < 20; i++) {
        for (int j = 1; j <= RoomCnt; j++) {
            cout << SparseCostTable[i][j] << " ";
        }
        cout << endl;
    }
}
// end DEBUG

void Input() {

    cin >> RoomCnt;
    for (int i = 1; i <= RoomCnt; i++) {
        cin >> AntEnergy[i];
    }

    for (int i = 1; i < RoomCnt; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        AdjList[u].push_back({v, c});
        AdjList[v].push_back({u, c});
    }
}

void BuildSparseTable() {
    // bfs를 통해서 level 0 부모 저장
    queue<int> q;
    vector<bool> visited(MAX_ROOM + 1, false);

    q.push(1);
    visited[1] = true;

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto [child, cost] : AdjList[cur]) {
            if (!visited[child]) {

                SparseTable[0][child] = cur;
                SparseCostTable[0][child] = cost;

                visited[child] = true;
                q.push(child);
            }
        }
    }

    // sparse table 채우기
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= RoomCnt; j++) {
            SparseTable[i][j] = SparseTable[i - 1][SparseTable[i - 1][j]];
        }
    }
}

void BuildSparseCostTable() {
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= RoomCnt; j++) {
            int next = SparseTable[i - 1][j];
            SparseCostTable[i][j] = SparseCostTable[i - 1][j] + SparseCostTable[i - 1][next];
        }
    }
}

LL GetMoveCost(int start, int move_cnt) {
    LL ret = 0;

    // use bitset
    bitset<20> bit(move_cnt);

    for (int i = 0; i < 20; i++) {
        if (bit[i]) {
            ret += SparseCostTable[i][start];
            start = SparseTable[i][start];
        }
    }

    return ret;
}

int GetMoveResult(int start, int move_cnt) {
    int ret = start;

    // use bitset
    bitset<20> bit(move_cnt);

    for (int i = 0; i < 20; i++) {
        if (bit[i]) {
            ret = SparseTable[i][ret];
        }
    }

    return ret;
}

int GetTopResult(int node, LL energy) {
    int result = node;

    for (int move_cnt = 0; move_cnt < MAX_ROOM; move_cnt++) {
        int result_node = GetMoveResult(node, move_cnt);
        if (result_node == 0) {
            break;
        }

        LL cost = GetMoveCost(node, move_cnt);

        if (cost > energy) {
            break;
        } else {
            result = result_node;
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();

    if (DEBUG) {
        cout << "finish input" << endl;
    }


    BuildSparseTable();

    BuildSparseCostTable();



    // DEBUG
    if(DEBUG) {
        cout << "Sparse Table" << endl;
        PrintSparseTable();
        cout << "Sparse Cost Table" << endl;
        PrintSparseCostTable();
    }
    // end DEBUG

    for(int i = 1; i <= RoomCnt; i++) {
        cout << GetTopResult(i, AntEnergy[i]) << " ";
    }

    return 0;
}