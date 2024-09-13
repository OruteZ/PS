#include<bits/stdc++.h>

using namespace std;

#define DEBUG 1

int BeadCount;
int GroupCount;

vector<int> Beads;

bool TryGroupBeads(int targetMinumum, vector<int>& groupSizes) {
    groupSizes.resize(GroupCount, 0);
    vector<int> groupWeights(GroupCount, 0);

    int curGroup = 0;
    for(int i = 0; i < BeadCount; i++) {
        while(true) {
            bool thisGroupAvailable = groupWeights[curGroup] + Beads[i] <= targetMinumum;

            if(thisGroupAvailable) {
                groupWeights[curGroup] += Beads[i];
                groupSizes[curGroup]++;
                break;
            } else {
                curGroup++;
                if(curGroup >= GroupCount) {
                    return false;
                }
            }
        }
    }

    //재조정 : 모든 그룹이 최소 하나씩은 가져야 함
    for(int i = GroupCount - 1; i > 0; i--) {
        if(groupSizes[i] <= 0) {
            int need = 1 - groupSizes[i];
            groupSizes[i] += need;
            groupSizes[i - 1] -= need;
        } else break;
    }

    return true;
}

void solution() {
    int left = 0;
    int right = accumulate(Beads.begin(), Beads.end(), 0);
    int result = right;

    while(left <= right) {

        int mid = (left + right) / 2;
        vector<int> groupResult;

        if(TryGroupBeads(mid, groupResult)) {
            result = min(result, mid);
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    vector<int> groupResult;
    TryGroupBeads(result, groupResult);

    cout << result << endl;
    for(int i = 0; i < GroupCount; i++) {
        cout << groupResult[i] << " ";
    }
}

int main() {
    cin >> BeadCount;
    cin >> GroupCount;

    Beads.resize(BeadCount);

    for (int i = 0; i < BeadCount; i++) {
        cin >> Beads[i];
    }

    solution();

    return 0;
}