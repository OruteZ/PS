#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'

//--------------------------------------------------

#define MAX_P 100000
#define MAX_A 100000

int next_gates[MAX_P + 1];

void Init() {
    // set up port
    int cnt = 0;
    for(int& i : next_gates) {
        i = cnt++;
    }
}

int GetNextGate(int gate_number) {
    if(gate_number == next_gates[gate_number]) return gate_number;

    int next = next_gates[gate_number];
    int new_next = GetNextGate(next);
    next_gates[gate_number] = new_next;

    return new_next;
}

void UpdateGate(int gate_number) {
    next_gates[gate_number] = GetNextGate(gate_number - 1);
}

bool TryDocking(int port_number) {
    int target = GetNextGate(port_number);
    if(target == 0) return false;

    UpdateGate(target);
    return true;
}

int main() {
    Init();
    int gates_cnt, plane_cnt;

    std::cin >> gates_cnt >> plane_cnt;

    int success_cnt = 0;

    while(plane_cnt--) {
        int target_gate;
        std::cin >> target_gate;

        if(TryDocking(target_gate)) success_cnt++;
        else break;
    }

    std::cout << success_cnt;
}

//---------------------------------------------------------

#pragma clang diagnostic pop