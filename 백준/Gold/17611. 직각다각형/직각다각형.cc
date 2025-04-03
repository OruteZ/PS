#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    int pos;
    int type;  // 0: 종료(close) 이벤트, 1: 시작(open) 이벤트
    int delta; // +1: 시작, -1: 종료
};

bool cmp(const Event &a, const Event &b) {
    if(a.pos == b.pos)
        return a.type < b.type;  // 같은 좌표에서는 종료 이벤트가 먼저 처리되도록
    return a.pos < b.pos;
}

int maxOverlap(const vector<pair<int,int>> &intervals) {
    vector<Event> events;
    // 각 interval이 (low, high) (열린 구간)임을 이용
    for(const auto &interval : intervals) {
        auto [low, high] = interval;
        // low와 high에서 각각 이벤트 생성
        events.emplace_back(Event{low, 1, +1});
        events.emplace_back(Event{high, 0, -1});
    }
    
    sort(events.begin(), events.end(), cmp);
    
    int cnt = 0;
    int ans = 0;
    int lastPos = events.empty() ? 0 : events[0].pos;
    
    for (const auto &e : events) {
        if(e.pos > lastPos) {
            // (lastPos, e.pos) 내에서 cnt가 일정하므로 최대값 갱신
            ans = max(ans, cnt);
        }
        cnt += e.delta;
        lastPos = e.pos;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<pair<int,int>> vertices(n);
    for (int i = 0; i < n; i++){
        cin >> vertices[i].first >> vertices[i].second;
    }
    
    // 수직변과 수평변의 열린 구간 저장
    vector<pair<int,int>> verticalIntervals;
    vector<pair<int,int>> horizontalIntervals;
    
    for (int i = 0; i < n; i++){
        int x1 = vertices[i].first, y1 = vertices[i].second;
        int x2 = vertices[(i+1) % n].first, y2 = vertices[(i+1) % n].second;
        if(x1 == x2) {
            // 수직변: y좌표가 다름 (열린 구간)
            int low = min(y1, y2), high = max(y1, y2);
            verticalIntervals.push_back({low, high});
        } else if(y1 == y2) {
            // 수평변: x좌표가 다름 (열린 구간)
            int low = min(x1, x2), high = max(x1, x2);
            horizontalIntervals.push_back({low, high});
        }
    }
    
    // 수평선 H가 수직변과 교차하는 최대 횟수
    int h = maxOverlap(verticalIntervals);
    // 수직선 V가 수평변과 교차하는 최대 횟수
    int v = maxOverlap(horizontalIntervals);
    
    cout << max(h, v) << "\n";
    return 0;
}
