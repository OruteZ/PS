#include<bits/stdc++.h>

#define MAX 4000000
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

// Table[i] = 가진 카드 중 i보다 큰 최소의 카드
vector<int> Table;
int N, M, K;

int get_min_big(int number) {
    stack<int> s;

    int value = Table[number];
    while(Table[value] != value) {
        s.push(value);
        value = Table[value];
    }

    int result = value;
    while(!s.empty()) {
        Table[s.top()] = result;
        s.pop();
    }

    return result;
}

void set_table() {
    vector<int> cards(M);

    for(int i = 0; i < M; i++) {
        cin >> cards[i];
    }

    sort(cards.begin(), cards.end());

    int cur_card = 0;
    for(int i = 1; i <= MAX; i++) {
        if(i > cards[cur_card]) {
            if(cur_card == M - 1) {
                break;
            }
            cur_card++;
        }

        Table[i] = cards[cur_card];
    }
}

int main() {
    FASTIO;

    cin >> N >> M >> K;
    Table.resize(MAX + 1);

    set_table();

    int target;
    for(int i = 0; i < K; i++) {
        cin >> target;

        if(Table[target] == target) {
            target++;
        }
        int card = get_min_big(target);
        Table[card] = get_min_big(card + 1);
        

        cout << card << '\n';
    }

}