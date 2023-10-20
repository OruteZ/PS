#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

typedef pair<int, int> point;

#define MAX 1000
#define DEBUG false

void print_info(point start,point dest) {
    cout << start.first << "," << start.second << '\n';
    cout << dest.first << "," << dest.second << '\n';
}

int dist_to_fuel(float dist) {
    int fuel = (int)dist / 10;
    if(fuel == dist) return fuel;
    else return fuel + 1;
}

int dist_to_fuel(point a, point b) {
    int x_diff_sqr = (a.first - b.first) * (a.first - b.first);
    int y_diff_sqr = (a.second - b.second) * (a.second - b.second);

    float dist = sqrt(x_diff_sqr + y_diff_sqr);

    return dist_to_fuel(dist);
}

point airfields[MAX + 2];
int max_fuels[MAX + 2][MAX + 1] = {0, };
int cnt;
int k;
int answer;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> cnt >> k;
    k++;

    int begin = 0;
    int end = cnt + 2;
    int last = cnt + 1;

    airfields[begin] = point(0, 0);
    airfields[last] = point(10000, 10000);

    for(int i = 1; i <= cnt; i++) {
        cin >> airfields[i].first >> airfields[i].second;
    }

    queue<int> container;
    container.push(begin);

    for(int t = 1; t <= k; t++) {
        if(DEBUG) cout << endl << t << endl;
        for(int i = begin; i < end; i++) {
            max_fuels[i][t] = max_fuels[i][t - 1];
        }

        int length = container.size();
        while(length--) {
            int cur = container.front();
            container.pop();

            for(int next = begin; next < end; next++) {
                if(cur == next) continue;

                int fuel = dist_to_fuel(airfields[cur], airfields[next]);
                fuel = max(max_fuels[cur][t - 1], fuel);

                //if not visited : fuel = max(currentFuel, distToFuel)
                if(max_fuels[next][t] == 0) {
                    max_fuels[next][t] = fuel;
                    container.push(next);
                }

                else {
                    if(max_fuels[next][t] <= fuel) continue;

                    max_fuels[next][t] = fuel;
                    container.push(next);
                }
            }
        }

        if(DEBUG) {
            for(int i = begin; i < end; i++) {
                cout << airfields[i].first << ":" << airfields[i].second << "--" << max_fuels[i][t] << endl;
            }
        }
    }

    cout << max_fuels[last][k];
}