#include<bits/stdc++.h>

using namespace std;

int main() {
    // fast io
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int student_cnt, video_cnt, time;
    cin >> student_cnt >> video_cnt >> time;
    time--;

    vector<int> cur_video(student_cnt, 0);
    vector<int> nxt_video(video_cnt, 0);

    for (int i = 0; i < student_cnt; i++) {
        cin >> cur_video[i];
        cur_video[i]--;
    }

    for (int i = 0; i < video_cnt; i++) {
        cin >> nxt_video[i];
        nxt_video[i]--;
    }

    // build sparse table
    // sparse_table[i][j] = i번 비디오부터 2^j분이 지났을 때, 현재 보는 비디오
    int maxPow = floor(log2(time)) + 1;
    vector<vector<int>> sparse_table(video_cnt, vector<int>(maxPow, 0));
    for(int start = 0; start < video_cnt; start++) {
        sparse_table[start][0] = nxt_video[start];
    }

    
    for (int t = 1; t < maxPow; t++) {
        for (int start = 0; start < video_cnt; start++) 
            sparse_table[start][t] = sparse_table[sparse_table[start][t - 1]][t - 1];
    }
    

    // debug : print sparse table
    // for (int i = 0; i < video_cnt; i++) {
    //     for (int j = 0; j < video_cnt; j++) {
    //         cout << sparse_table[i][j] + 1 << ' ';
    //     }
    //     cout << '\n';
    // }


    // time 후에 각 학생이 보게 될 비디오의 번호
    for (int i = 0; i < student_cnt; i++) {
        int cur = cur_video[i];

        for (int j = 0; j < maxPow; j++) {
            if (time & (1 << j)) {
                cur = sparse_table[cur][j];
            }
        }
        cout << cur + 1 << ' ';
    }
}

