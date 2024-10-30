#include <iostream>
#include <map>
#include <vector>
#include <stack>

using namespace std;
typedef long long int ll;

int N;
int W;
vector<pair<int ,int>> points;
map<pair<int, int>, ll> Dictionary;


int Calculate_distance(pair<int, int> point1, pair<int, int> point2) {
    return abs(point1.first - point2.first) + abs(point1.second - point2.second);
}

ll Recursion(int last_1, int last_2) {
    //진짜 마지막으로 제거한 사건 = 두 값중 최대값
    int last_index = last_1 >= last_2 ? last_1 : last_2;
    if(last_index == points.size()-1) return 0;

    //memoization
    if(Dictionary.find(make_pair(last_1, last_2)) != Dictionary.end()) {
        return Dictionary[make_pair(last_1, last_2)];
    }

    pair<int, int> now_case_point = points[last_index+1];

    //case 1 : 1번차가 이동할때
    ll val1 = Recursion(last_index + 1, last_2);
    val1 += Calculate_distance(points[last_1], now_case_point);

    //case 2 : 2번차가 이동할 때
    ll val2 = Recursion(last_1, last_index + 1);
    val2 += Calculate_distance(points[last_2], now_case_point);

    ll answer;
    if(val1 <= val2) {
        answer = val1;
    }
    else {
        answer = val2;
    }
    Dictionary[make_pair(last_1, last_2)] = answer;

    return answer;
}

void Route(int last_1, int last_2) {
    int last_index = last_1 > last_2 ? last_1 : last_2;
    if(last_index == W+1) return;

    pair<int, int> now_case_point = points[last_index+1];

    ll val1 = Dictionary[make_pair(last_index + 1, last_2)];
    val1 += Calculate_distance(points[last_1], now_case_point);

    ll val2 = Dictionary[make_pair(last_1, last_index + 1)];
    val2 += Calculate_distance(points[last_2], now_case_point);

    if(val1 <= val2) {
        cout << 1 << '\n';
        Route(last_index + 1, last_2);
    } else {
        cout << 2 << '\n';
        Route(last_1, last_index + 1);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    cin >> N >> W;
    int a, b;

    points.emplace_back(1, 1);
    points.emplace_back(N, N);
    for(int i = 0; i < W; i++) {
        cin >> a >> b;
        points.emplace_back(a, b);
    }

    ll result = Recursion(0, 1);
    cout << result <<'\n';
    Route(0,1);

    return 0;
}