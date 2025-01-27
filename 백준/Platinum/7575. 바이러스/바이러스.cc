#include <bits/stdc++.h>
#define MOD 10007
#define MAX 1'000'000

using namespace std;
typedef long long ll;

typedef vector<int> program;
typedef program::iterator pIter;
typedef program::reverse_iterator rpIter;

// O(n)
bool contains_virus(
    pIter start, 
    pIter end, 
    pIter sub_start,
    pIter sub_end,
    const vector<int>& pi
    ) {
    // use kmp

    int j = 0;
    for (int i = 0; i < end - start; i++) {
        while (j > 0 && start[i] != sub_start[j]) {
            j = pi[j - 1];
        }
        if (start[i] == sub_start[j]) {
            if (j == sub_end - sub_start - 1) {
                return true;
            }
            j++;
        }
    }

    return false;
}

bool contains_virus (
    rpIter start, 
    rpIter end, 
    pIter sub_start,
    pIter sub_end,
    const vector<int>& pi
    ) {
    // use kmp. reversed

    int j = 0;
    for (int i = 0; i < end - start; i++) {
        while (j > 0 && start[i] != sub_start[j]) {
            j = pi[j - 1];
        }
        if (start[i] == sub_start[j]) {
            if (j == sub_end - sub_start - 1) {
                return true;
            }
            j++;
        }
    }

    return false;
}


// O(n)
vector<int> getPi(pIter begin, pIter end) {
    vector<int> pi(end - begin, 0);
    int j = 0;
    for (int i = 1; i < end - begin; i++) {
        while (j > 0 && begin[i] != begin[j]) {
            j = pi[j - 1];
        }
        if (begin[i] == begin[j]) {
            pi[i] = ++j;
        }
    }
    return pi;
}

int main() {

    //======================= KMP Test Code =======================
    // vector<int> test_program = {1, 2, 3, 4, 4, 3, 2, 5};
    // vector<int> test_sub = {2, 3, 4};

    // vector<int> pi = getPi(test_sub.begin(), test_sub.end());

    // if (contains_virus(test_program.begin(), test_program.end(), test_sub.begin(), test_sub.end(), pi)) {
    //     cout << "Subsequence found in the program." << endl;
    // } else {
    //     cout << "Subsequence not found in the program." << endl;
    // }

    // if (contains_virus(test_program.rbegin(), test_program.rend(), test_sub.begin(), test_sub.end(), pi)) {
    //     cout << "Subsequence found in the reversed program." << endl;
    // } else {
    //     cout << "Subsequence not found in the reversed program." << endl;
    // }

    //================================================================
    int program_cnt, min_virus;
    int program_size;
    cin >> program_cnt >> min_virus;

    vector<program> programs(program_cnt);
    for (int i = 0; i < program_cnt; i++) {
        cin >> program_size;
        programs[i].resize(program_size);
        for (int j = 0; j < program_size; j++) {
            cin >> programs[i][j];
        }
    }

    pIter sub_start;
    pIter sub_end;
    rpIter r_sub_start;
    rpIter r_sub_end;
    for(int i = 0; i < programs[0].size() - min_virus + 1; i++) {
        //cout << "i: " << i << endl;

        sub_start = programs[0].begin() + i;
        sub_end = programs[0].begin() + i + min_virus;

        // test. print subsequence
        // cout << "subsequence: " << endl;
        // for (auto it = sub_start; it != sub_end; it++) {
        //     cout << *it << " ";
        // }
        // cout << endl;

        // build pi
        vector<int> pi = getPi(sub_start, sub_end);
        bool contains = true;

        for (int j = 1; j < program_cnt; j++) {
            // 각 프로그램이 reverse포함해서 kmp 성립되는지 확인

            bool success = 
                contains_virus(programs[j].begin(), programs[j].end(), sub_start, sub_end, pi) or 
                contains_virus(programs[j].rbegin(), programs[j].rend(), sub_start, sub_end, pi);


            if (!success) {
                // cout << "failed at " << j << endl;
                contains = false;
                break;
            }

        }

        if (contains) {
            cout << "YES" << endl;
            return 0;
        } 

        // cout << endl;
    }

    cout << "NO" << endl;
    
}