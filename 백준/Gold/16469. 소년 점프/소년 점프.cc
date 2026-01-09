#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

vector<vector<int>> bfs_grid(const vector<string>& grid, int start_i, int start_j) {
    int height = (int)grid.size();
    int width = (int)grid[0].size();
    vector<vector<int>> dist(height, vector<int>(width, -1));

    
    queue<pair<int, int>> q;
    if (grid[start_i][start_j] != '0') return dist; // 보통 입력상 여기 오지 않음

    dist[start_i][start_j] = 0;
    q.emplace(start_i, start_j);

    int di[4] = {1, -1, 0, 0};
    int dj[4] = {0, 0, 1, -1};

    while (not q.empty()) {
        auto [ci, cj] = q.front();
        q.pop();

        for (int k = 0; k < 4; k++) {
            int ni = ci + di[k], nj = cj + dj[k];
            if (ni < 0 || ni >= height || nj < 0 || nj >= width) continue;
            if (grid[ni][nj] != '0') continue;

            
            if (dist[ni][nj] != -1) continue;
            dist[ni][nj] = dist[ci][cj] + 1;
            q.emplace(ni, nj);
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int height, width;
    cin >> height >> width;
    vector<string> grid(height);
    for (int i = 0; i < height; i++) cin >> grid[i];

    int ai, aj, bi, bj, ci, cj;
    cin >> ai >> aj;
    cin >> bi >> bj;
    cin >> ci >> cj;
    ai--; aj--; bi--; bj--; ci--; cj--;

    auto da = bfs_grid(grid, ai, aj);
    auto db = bfs_grid(grid, bi, bj);
    auto dj = bfs_grid(grid, ci, cj);

    int best = INF, cnt = 0;
    for (int i = 0; i < height; i++) for(int j = 0; j < width; j++) {
        if (da[i][j] < 0 || db[i][j] < 0 || dj[i][j] < 0) continue;
        int t = max({da[i][j], db[i][j], dj[i][j]});

        if (t < best) {
            best = t;
            cnt = 1;
        } else if (t == best) {
            cnt++;
        }
    }

    if (cnt == 0) {
        cout << -1 << "\n";
    } else {
        cout << best << "\n" << cnt << "\n";
    }
    return 0;
}
