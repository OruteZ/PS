#include<bits/stdc++.h>

#define REPEAT(N) for(int _ = 0; _ < (N); _++)

int PartyCount, UserCount;
std::vector<std::vector<int>> Graph;
std::vector<std::vector<int>> MinDist;

void build_MinDist() {
    MinDist.assign(PartyCount, std::vector<int>(PartyCount, 0));
    for (int i = 0; i < PartyCount; i++) {
        for (int j = 0; j < PartyCount; j++) {
            MinDist[i][j] = Graph[i][j];
        }
    }

    for (int k = 0; k < PartyCount; k++) {
        for (int i = 0; i < PartyCount; i++) {
            for (int j = 0; j < PartyCount; j++) {
                MinDist[i][j] = std::min(MinDist[i][j], MinDist[i][k] + MinDist[k][j]);
            }
        }
    }
}

void handle_query() {
    int begin, dest, budget;

    std::cin >> begin >> dest >> budget;
    begin--; dest--;

    if (MinDist[begin][dest] <= budget) {
        std::cout << "Enjoy other party\n";
    } else {
        std::cout << "Stay here\n";
    }
}

int main() {
    std::cin >> PartyCount >> UserCount;

    Graph.assign(PartyCount, std::vector<int>(PartyCount, 0));
    for (int i = 0; i < PartyCount; i++) {
        for (int j = 0; j < PartyCount; j++) {
            std::cin >> Graph[i][j];
        }
    }

    build_MinDist();

    REPEAT(UserCount) handle_query();
}