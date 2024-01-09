#include<iostream>
#include<queue>

typedef std::pair<int, int> PII;

// 이동 기록을 저장할 Queue
std::queue<PII> move_record;

// start 위치에 있는 원판 n개를 end로 옮기는 과정
// 그 과정에서 일어나는 이동이 모두 출력 됨
void move(int start, int end, int count) {
    //base case : 옮기는 원판이 하나일 경우 그냥 출력
    if(count == 1) {
        move_record.emplace(start, end);
        return;
    }

    //원판을 옮기는 방법은 다음과 같다.
    // 1. 가장 큰 원판을 남기고 나머지를 start도 end도 아닌 남은 한칸으로 이주

    int middle_point = 6 - start - end; //1, 2, 3번칸만 있으니까 6에서 빼면 나옴
    move(start, middle_point, count - 1);

    // 2. 가장 큰 원판을 목적지로 이주
    move_record.emplace(start, end);

    // 3. 나머지 원판을 다시 이주
    move(middle_point, end, count - 1);
}

int main() {
    int n;

    std::cin >> n;
    move(1, 3, n);

    std::cout << move_record.size() << '\n';
    while(move_record.empty() == false) {
        PII record = move_record.front();
        move_record.pop();

        std::cout << record.first << ' ' << record.second << '\n';
    }
}
