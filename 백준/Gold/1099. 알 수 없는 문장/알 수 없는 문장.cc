#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];

    int Ls = (int)S.size();

    // prefix counts for S
    vector<array<int, 26>> pre(Ls + 1);
    pre[0].fill(0);
    for (int i = 0; i < Ls; i++) {
        pre[i + 1] = pre[i];
        pre[i + 1][S[i] - 'a']++;
    }

    // word counts
    vector<array<int, 26>> wc(n);
    for (int i = 0; i < n; i++) {
        wc[i].fill(0);
        for (char ch : words[i]) wc[i][ch - 'a']++;
    }

    vector<int> dp(Ls + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < Ls; i++) {
        if (dp[i] == INF) continue;

        for (int w = 0; w < n; w++) {
            int len = (int)words[w].size();
            if (i + len > Ls) continue;

            // anagram check via counts
            bool ok = true;
            for (int c = 0; c < 26; c++) {
                int cnt = pre[i + len][c] - pre[i][c];
                if (cnt != wc[w][c]) { ok = false; break; }
            }
            if (!ok) continue;

            // cost = Hamming distance between words[w] and S[i..i+len-1]
            int cost = 0;
            for (int k = 0; k < len; k++) {
                if (S[i + k] != words[w][k]) cost++;
            }

            dp[i + len] = min(dp[i + len], dp[i] + cost);
        }
    }

    cout << (dp[Ls] == INF ? -1 : dp[Ls]) << "\n";
    return 0;
}
