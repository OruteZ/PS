#include<bits/stdc++.h>

using namespace std;

int N;
vector<pair<int, int>> Points;

double GetTriangleArea(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	return 0.5 * abs(
		a.first * b.second +
		b.first * c.second +
		c.first * a.second -
		a.second * b.first -
		b.second * c.first -
		c.second * a.first);
}

int main() {
	cin >> N;
	Points.resize(N);

	for(int i = 0; i < N; i++) {
		cin >> Points[i].first >> Points[i].second;
	}

	double result = 0;
	for(int i = 0; i < N; i++) {
		for(int j = i + 1; j < N; j++) {
			for(int k = j + 1; k < N; k++) {
				result = max(result, GetTriangleArea(Points[i], Points[j], Points[k]));
			}
		}
	}
	cout << fixed;
	cout.precision(9);
	cout << result << endl;
}