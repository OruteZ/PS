#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, d, k, c;
    cin >> N >> d >> k >> c;
    
    // 벨트 위의 초밥 종류를 저장할 vector
    vector<int> sushi(N);
    for (int i = 0; i < N; i++) {
        cin >> sushi[i];
    }
    
    // 초밥 종류별 개수 저장 (1번부터 d번까지 사용)
    vector<int> count(d + 1, 0);
    int distinct = 0;  // 현재 윈도우에 있는 서로 다른 초밥의 개수
    
    // deque를 사용하여 현재 윈도우의 초밥을 저장
    deque<int> window;
    
    // 초기 윈도우 설정: 처음 k개 접시 처리
    for (int i = 0; i < k; i++) {
        int s = sushi[i];
        window.push_back(s);
        if (count[s] == 0) {
            distinct++;
        }
        count[s]++;
    }
    
    // 쿠폰 초밥을 고려하여 최대 가짓수 계산
    int answer = distinct + (count[c] == 0 ? 1 : 0);
    
    // 슬라이딩 윈도우 진행 (원형 구조 고려)
    // 총 N개의 시작 위치에 대해 검사
    for (int i = 1; i < N; i++) {
        // deque의 맨 앞 접시 제거
        int removeSushi = window.front();
        window.pop_front();
        count[removeSushi]--;
        if (count[removeSushi] == 0)
            distinct--;
        
        // 새로 추가할 초밥의 인덱스 (원형 구조를 위해 모듈로 연산)
        int addIndex = (i + k - 1) % N;
        int addSushi = sushi[addIndex];
        window.push_back(addSushi);
        if (count[addSushi] == 0)
            distinct++;
        count[addSushi]++;
        
        // 쿠폰 초밥이 없으면 1을 추가
        int current = distinct + (count[c] == 0 ? 1 : 0);
        answer = max(answer, current);
    }
    
    cout << answer << "\n";
    return 0;
}
