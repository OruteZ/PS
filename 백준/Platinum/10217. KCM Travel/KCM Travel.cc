#include <bits/stdc++.h>

using namespace std;

#define END_L '\n'
#define MAX 2'000'000'000
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

#define MAX_AIRPORT_COUNT 100
#define MAX_BUDGET 10000

struct Ticket {
    int to;

    int cost;
    int time;
};

// tickets[출발지] = {출발지, 도착지, 비용, 시간}
vector<vector<Ticket>> tickets;

int AirportCount;
int TicketCount;
int TotalBudget;

int Dp[MAX_AIRPORT_COUNT+1][MAX_BUDGET+1];

void Input() {
    cin >> AirportCount >> TotalBudget >> TicketCount;

    tickets.clear();
    tickets.resize(AirportCount+1);
    for(int i=0; i<TicketCount; i++) {
        int start, to, cost, time;
        cin >> start >> to >> cost >> time;
        tickets[start].push_back({to, cost, time});
    }

    // sort tickets by time
    for(int i=1; i<=AirportCount; i++) {
        sort(tickets[i].begin(), tickets[i].end(), [](const Ticket& a, const Ticket& b) {
            return a.time < b.time;
        });
    }

	// fill Dp
	fill(&Dp[0][0], &Dp[MAX_AIRPORT_COUNT][MAX_BUDGET+1], -1);
}

// airport 공항서 목적지 공항 까지 budget 을 가지고 갈 때의 최소 시간
int GetMinTime(int airport, int budget) {
    if(airport == AirportCount) return 0;

    int& ret = Dp[airport][budget];
    if(ret != -1) return ret;

    ret = MAX;
    for(auto& ticket : tickets[airport]) {
        if(budget >= ticket.cost) {
            ret = min(ret, ticket.time + GetMinTime(ticket.to, budget - ticket.cost));
        }
    }

    return ret;
}

void solution() {
    int ret = GetMinTime(1, TotalBudget);

    if(ret == MAX) cout << "Poor KCM" << END_L;
    else cout << ret << END_L;
}

int main() {
    FAST_IO;
    int t_case;
    cin >> t_case;

    while(t_case--) {
        Input();
        solution();
    }
}
